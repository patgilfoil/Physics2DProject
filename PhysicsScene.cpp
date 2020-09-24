#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include <list>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto actor : m_actors) {
		delete actor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor) {
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor) {
	for (auto i = m_actors.begin(); i < m_actors.end(); i++) {
		if (*i == actor) {
			m_actors.erase(i);
		}
	}
}

void PhysicsScene::update(float deltaTime)
{
	static std::list<PhysicsObject*> dirty;

	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;
	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		checkForCollision();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene() {
	for (auto actor : m_actors) {
		actor->debug();
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] = {
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
};

void PhysicsScene::checkForCollision() {
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			int functionIdx = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr) {
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane1 = dynamic_cast<Plane*>(object1);
	Plane* plane2 = dynamic_cast<Plane*>(object2);
	if (plane1 != nullptr && plane2 != nullptr) {
		if (plane1->getNormal().x != plane2->getNormal().x || plane1->getNormal().y != plane2->getNormal().y) {
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* object1, PhysicsObject* object2) {
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);
	//if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		float sphereToPlaneDistance =
			glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

		// if we are behind plane then we flip the normal
		glm::vec2 collisionNormal = plane->getNormal();
		if (sphereToPlaneDistance < 0) {
			collisionNormal *= -1;
			sphereToPlaneDistance *= -1;
		}

		sphereToPlaneDistance -= sphere->getRadius();
		if (sphereToPlaneDistance <= 0) {
			glm::vec2 contact = sphere->getPosition() - (collisionNormal * sphere->getRadius());
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}
	return false;

}

bool PhysicsScene::plane2Sphere(PhysicsObject* object1, PhysicsObject* object2)
{
	sphere2Plane(object2, object1);
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* object1, PhysicsObject* object2) {
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);
	if (sphere1 == nullptr && sphere2 == nullptr) {
		return glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius();
	}
	return false;
}