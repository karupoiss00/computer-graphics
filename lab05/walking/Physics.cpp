#include <algorithm>
#include <iostream>
#include "Physics.h"
#include "Math.h"

constexpr double MIN_SPEED = 0.1;

Physics::Physics(ICollisionProvider& collision, double gConst)
	: m_collisionProvider(collision)
	, m_gravity({0, -gConst, 0})
{

}

void Physics::AddObject(PhysicalObject* object)
{
	m_objects.push_back(object);
}

void Physics::RemoveObject(PhysicalObject* object)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), object);

	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
}

void Physics::Update(double dt)
{
	ApplyDynamics(dt);
	ResolveCollisions();
}

void Physics::ResolveCollisions()
{
	for (auto& object : m_objects)
	{
		auto currentVelocity = object->GetVelocity();
		auto currentPosition = object->GetPosition();
		auto collisionClamp = m_collisionProvider.GetCollision(object->GetBox()).clamp;

		object->SetPosition(currentPosition + collisionClamp);

		if (collisionClamp.x)
		{
			currentVelocity.x = 0;
		}

		if (collisionClamp.y)
		{
			if (abs(currentVelocity.y) > MIN_SPEED)
			{
				if (!IsEqual(object->GetElasticity(), 0))
				{
					std::cout << currentVelocity.y << std::endl;
				}
				currentVelocity.y = -currentVelocity.y * object->GetElasticity();
			}
			else
			{
				currentVelocity.y = 0;
			}
		}

		if (collisionClamp.z)
		{
			currentVelocity.z = 0;
		}

		object->SetVelocity(currentVelocity);
	}
}

void Physics::ApplyDynamics(double dt)
{
	for (auto& object : m_objects)
	{
		auto force = object->GetMass() * m_gravity;
		auto currentVelocity = object->GetVelocity();
		auto currentPosition = object->GetPosition();

		object->SetVelocity(currentVelocity + force / object->GetMass() * dt);
		object->SetPosition(currentPosition + object->GetVelocity() * dt);
	}
}