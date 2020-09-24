#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass) :
	PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_velocity += gravity * timeStep;
	if (glm::length(m_velocity) < 0.01f)
		m_velocity = glm::vec2(0.0f, 0.0f);
	m_position += m_velocity * timeStep;
}

void RigidBody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	m_velocity += force / m_mass;
	m_angularVelocity += ((force.y * pos.x) - (force.x * pos.y) / m_moment);
}

void RigidBody::resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal)
{
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal : other->getPosition() - m_position);
	glm::vec2 perpendicular(normal.y, -normal.x);

	float radius = glm::dot(contact - m_position, -perpendicular);
	float otherRadius = glm::dot(contact - other->getPosition(), perpendicular);

	float velocity = glm::dot(m_velocity, normal) - radius * m_angularVelocity;
	float otherVelocity = glm::dot(other->getVelocity(), normal) +
		otherRadius * other->getAngularVelocity();

	if (velocity <= otherVelocity) return;

	float mass = 1.0f / (1.0f / m_mass + (radius * radius) / m_moment);
	float otherMass = 1.0f / (1.0f / other->getMass() +
		(otherRadius * otherRadius) / other->getMoment());

	float elasticity = (m_elasticity + other->getElasticity()) / 2;
	glm::vec2 force = (1.0f + elasticity) * mass * otherMass /
		(mass + otherMass) * (velocity - otherVelocity) * normal;

	other->applyForce(force, contact - other->getPosition());
	applyForce(-force, contact - m_position);
}