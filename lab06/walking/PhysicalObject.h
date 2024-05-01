#pragma once
#include <map>
#include "Direction.h"
#include "Collision.h"

class PhysicalObject
{
public:
	explicit PhysicalObject(Collision::BoundingBox box, double mass = 1.0, double elasticity = 0);

	void SetPosition(glm::dvec3 position);
	void SetVelocity(glm::dvec3 velocity);

	double GetMass() const;
	double GetElasticity() const;
	glm::dvec3 GetVelocity() const;
	glm::dvec3 GetPosition() const;
	Collision::BoundingBox GetBox() const;
private:
	Collision::BoundingBox m_box;
	glm::dvec3 m_velocity;
	double m_mass;
	double m_elasticity;
};