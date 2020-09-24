#pragma once
#include "RigidBody.h"
class Sphere : public RigidBody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color);
	~Sphere() {}

	virtual void makeGizmo();
	virtual bool checkCollision(PhysicsObject* other);

	float getRadius() { return m_radius; }
	glm::vec4 getColor() { return m_color; }

protected:
	float m_radius;
	glm::vec4 m_color;
};

