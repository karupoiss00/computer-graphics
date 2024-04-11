#include <algorithm>
#include "Gravity.h"
#include "Math.h"

Gravity::Gravity(double gConst)
	: m_gConst(gConst)
{

}

void Gravity::AddObject(IGravityObject* object)
{
	m_objects.push_back(object);
}

void Gravity::RemoveObject(IGravityObject* object)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), object);

	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
}

void Gravity::Update(double deltaTime)
{
	for (auto& object : m_objects)
	{
		auto elasticity = Normalize(object->GetElasticity());
		auto currentSpeed = object->GetVerticalSpeed();
		
		if (IsEqual(currentSpeed, 0) && !object->CanDrop())
		{
			continue;
		}

		if (currentSpeed < 0 && !object->CanDrop())
		{
			object->SetVerticalSpeed(-currentSpeed * elasticity);
		}
		else
		{
			object->SetVerticalSpeed(
				currentSpeed - m_gConst * deltaTime
			);
		}
	}
}