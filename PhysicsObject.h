#pragma once
#include <glm/ext.hpp>

/**
* ShapeType is used to determine the function used to solve collision when two objects collide
*/
enum ShapeType {
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};

/**
* PhysicsObject serves as the baseline for all objects that resolve collision
*/
class PhysicsObject {
protected:
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {}

	ShapeType getShapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};