#pragma once
#include"PhysicsObject.h"
class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity);
	~RigidBody() {}

	virtual void fixedUpdate(float timeStep);
	virtual void debug() {}

	void applyForce(glm::vec2 force, glm::vec2 pos);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;
	void resolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setPosition(glm::vec2 position) { m_position = position; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
};

