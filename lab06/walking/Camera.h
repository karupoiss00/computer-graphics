#pragma once
#include "ViewDirectionProvider.h"

class Camera : public IViewDirectionProvider
{
public:
	explicit Camera();

	void Rotate(double mouseX, double mouseY);

	void SetPosition(glm::dvec3 position);

	glm::dvec3 GetDirectionProjection(Direction dir) override;

	glm::dmat4 GetWorldToViewMatrix() const;

	glm::dvec3 GetLookDirection() const;

	double GetVerticalAngle() const;

	double GetMaxVerticalAngle() const;

	double GetMinVerticalAngle() const;
private:
	glm::dvec3 m_cameraPos;
	glm::dvec3 m_lookDirection;
};