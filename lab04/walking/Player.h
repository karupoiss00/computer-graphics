#pragma once

class Player
{
public:
	Player();

	void SetPosition(glm::dvec3 position);
	glm::dvec3 GetPosition() const;
private:
	glm::dvec3 m_position;
};