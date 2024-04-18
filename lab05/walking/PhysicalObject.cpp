#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(BoundingBox box, double mass,  double elasticity)
	: m_box(box)
	, m_elasticity(elasticity)
	, m_velocity(0, 0, 0)
	, m_mass(mass)
{
}

void PhysicalObject::SetPosition(glm::dvec3 position)
{
	m_box.position = position;
}

void PhysicalObject::SetVelocity(glm::dvec3 velocity)
{
	m_velocity = velocity;
}

glm::dvec3 PhysicalObject::GetVelocity() const
{
	return m_velocity;
}

double PhysicalObject::GetElasticity() const
{
	return m_elasticity;
}

double PhysicalObject::GetMass() const
{
	return m_mass;
}

glm::dvec3 PhysicalObject::GetPosition() const
{
	return m_box.position;
}

BoundingBox PhysicalObject::GetBox() const
{
	return m_box;
}