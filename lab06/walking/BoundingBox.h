#pragma once
#include <glm/glm.hpp>

class BoundingBox
{

public:
	BoundingBox();
	BoundingBox(glm::vec3 const& minCoord, glm::vec3 const& maxCoord);

	bool IsEmpty() const;
	BoundingBox const Union(BoundingBox const& other) const;
	glm::vec3 const& GetMinCoord() const;
	glm::vec3 const& GetMaxCoord() const;
	glm::vec3 const GetSize() const;
	glm::vec3 const GetCenter() const;
private:
	bool m_isEmpty;
	glm::vec3 m_minCoord;
	glm::vec3 m_maxCoord;
};