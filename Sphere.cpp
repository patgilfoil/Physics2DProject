#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color) :
	RigidBody(SPHERE, position, velocity, mass)
{
	m_radius = radius;
	m_color = color;
}

/**
* Makes a "gizmo" that draws to the window space
*/
void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);
}

bool Sphere::checkCollision(PhysicsObject* other) {
	return false;
}