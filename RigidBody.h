#pragma once
#include"PhysicsObject.h"
class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float mass);
	~RigidBody() {}

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {}

	void applyForce(glm::vec2 force, glm::vec2 pos);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;

	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	float getAngularVelocity() { return m_angularVelocity; }
	float getElasticity() { return m_elasticity; }
	float getMoment() { return m_moment; }

	void setPosition(glm::vec2 position) { m_position = position; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	void setMass(float mass) { m_mass = mass; }
	void setElasticity(float value) { m_elasticity = value; }

protected:
	/**
	* Object position
	*/
	glm::vec2 m_position;
	/**
	* Object velocity
	*/
	glm::vec2 m_velocity;
	/**
	* Object mass
	*/
	float m_mass;
	/**
	* Object angular velocity
	*/
	float m_angularVelocity;
	/**
	* Object elasticity, defaults to 1.0
	*/
	float m_elasticity = 1.0f;
	/**
	* Helps solve angular velocity
	*/
	float m_moment;
};

