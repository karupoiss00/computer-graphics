#pragma once
#include <vector>
#include "PhysicalObject.h"
#include "CollisionProvider.h"

class Physics
{
public:
	Physics(ICollisionProvider& collision, double gConst);

	void AddObject(PhysicalObject* object);
	void RemoveObject(PhysicalObject* object);
	void Update(double deltaTime);

private:
	void ResolveCollisions();
	void ApplyDynamics(double dt);

	glm::dvec3 m_gravity;
	std::vector<PhysicalObject*> m_objects;
	ICollisionProvider& m_collisionProvider;
};