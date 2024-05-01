#include <stdexcept>
#include "BoundingBox.h"

BoundingBox::BoundingBox()
	: m_isEmpty(true)
{

}

BoundingBox::BoundingBox(glm::vec3 const& minCoord, glm::vec3 const& maxCoord)
	: m_minCoord(minCoord)
	, m_maxCoord(maxCoord)
	, m_isEmpty(false)
{

}

glm::vec3 const& BoundingBox::GetMinCoord()const
{
	if (m_isEmpty)
	{
		throw std::logic_error("Bounding box is empty");
	}

	return m_minCoord;
}

glm::vec3 const& BoundingBox::GetMaxCoord()const
{
	if (m_isEmpty)
	{
		throw std::logic_error("Bounding box is empty");
	}

	return m_maxCoord;
}

glm::vec3 const BoundingBox::GetSize()const
{
	if (m_isEmpty)
	{
		return { 0, 0, 0 };
	}

	return m_maxCoord - m_minCoord;
}

glm::vec3 const BoundingBox::GetCenter() const
{
	if (m_isEmpty)
	{
		throw std::logic_error("Bounding box is empty");
	}

	return (m_minCoord + m_maxCoord) * 0.5f;
}

BoundingBox const BoundingBox::Union(BoundingBox const& other) const
{
	if (m_isEmpty && other.m_isEmpty)
	{
		return BoundingBox();
	}
	else if (m_isEmpty)
	{
		return other;
	}
	else if (other.m_isEmpty)
	{
		return *this;
	}
	else
	{
		using namespace std;

		return BoundingBox(
			{

				min(m_minCoord.x, other.m_minCoord.x),
				min(m_minCoord.y, other.m_minCoord.y),
				min(m_minCoord.z, other.m_minCoord.z)
			},
			{
				max(m_maxCoord.x, other.m_maxCoord.x),
				max(m_maxCoord.y, other.m_maxCoord.y),
				max(m_maxCoord.z, other.m_maxCoord.z)
			}
		);
	}
}

bool BoundingBox::IsEmpty() const
{
	return m_isEmpty;
}