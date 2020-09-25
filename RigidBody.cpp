#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass) :
	PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
}

/**
* Updates object every timeStep
*/
void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_velocity += gravity * timeStep;
	if (glm::length(m_velocity) < 0.01f)
		m_velocity = glm::vec2(0.0f, 0.0f);
	m_position += m_velocity * timeStep;
}

/**
* Applies a force to an object to modify it's velocity and angular velocity
*/
void RigidBody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	m_velocity += force / m_mass;
	m_angularVelocity += ((force.y * pos.x) - (force.x * pos.y) / m_moment);
}