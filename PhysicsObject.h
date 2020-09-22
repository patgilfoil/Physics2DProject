#pragma once
#include <glm/ext.hpp>

enum ShapeType {
	BOX = 0,
	SPHERE,
	SHAPE_COUNT
};

class PhysicsObject {
protected:
	PhysicsObject();

public:
	virtual void fixedUpdate( float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {}
};