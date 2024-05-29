#include "stdafx.h"
#include "PhongLightShader.h"
#include "Vector4.h"
#include "Scene.h"
#include "Intersection.h"
#include "Ray.h"
#include "ShadeContext.h"
#include "ILightSource.h"
#include "VectorMath.h"

CPhongLightShader::CPhongLightShader(void)
{
}

/*
Запоминаем параметры материала, связанного с шейдером
*/
void CPhongLightShader::SetMaterial(CSimpleMaterial const& material)
{
	m_material = material;
}

CVector4f CPhongLightShader::Shade(CShadeContext const & shadeContext)const
{
	/*
	Получаем сцену из контекста закрашивания для того, чтобы вычислить вклад
	каждого из источников света в освещенность обрабатываемой точки
	*/
	CScene const& scene = shadeContext.GetScene();

	// Результирующий цвет
	CVector4f shadedColor;

	const size_t numLights = scene.GetLightsCount();

	// Пробегаемся по всем источникам света в сцене
	for (size_t i = 0; i < numLights; ++i)
	{
		// Получаем источник света
		ILightSource const& light = scene.GetLight(i);

		auto& surfacePoint = shadeContext.GetSurfacePoint();

		auto lightDirection = light.GetDirectionFromPoint(surfacePoint);
		/*
		static const unsigned COUNT_OF_SHADOW_RAYS = 7;
		auto lightDirections = light.GetAllDirectionsFromPoint(surfacePoint, COUNT_OF_SHADOW_RAYS);
		unsigned raysWithoutHitCount = 0;
		for (auto dir : lightDirections)
		{
			CSceneObject const* pSceneObject = NULL;
			CIntersection intersection;
			CRay shadowRay(surfacePoint, dir);
			
			if (!scene.GetFirstHit(shadowRay, intersection, &pSceneObject))
			{
				raysWithoutHitCount++;
			}
		}*/

		// Определяем, находится ли объект в тени
		CSceneObject const* pSceneObject = NULL;
		CIntersection intersection;
		CRay shadowRay(surfacePoint, lightDirection);
		bool shadowed = scene.GetFirstHit(shadowRay, intersection, &pSceneObject);

		// Вычисляем интенсивность света в направлении от источника к текущей точке
		double lightIntensity = light.GetIntensityInDirection(-lightDirection);// * (raysWithoutHitCount / COUNT_OF_SHADOW_RAYS);

		if (shadowed) 
		{
			lightIntensity = 0;
		}

		// Получаем нормаль к поверхности в обрабатываемой точке
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		// Вычисляем скалярное произведение нормали и орт-вектора направления на источник света
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

		// Вычисляем диффузный цвет точки
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();

		// К результирующему цвету прибавляется вычисленный диффузный цвет
		shadedColor += diffuseColor;

		// вектор отраженного света R
		CVector3d reflectedLightVector = Normalize(2 * Dot(n, Normalize(lightDirection)) * n - lightDirection);

		CVector3d observerVector = Normalize(CVector3d(0, 2.5, 7) - shadeContext.GetSurfacePoint()); // вектор от позиции камеры к точке
		CVector4f specularColor = m_material.GetSpecularColor() * light.GetSpecularIntensity() * float(pow(Max(0.0, Dot(reflectedLightVector, observerVector)), m_material.GetShiness()));

		shadedColor += specularColor;

		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor();
		shadedColor += ambientColor;
	}	// Проделываем данные действия для других источников света

	// Возвращаем результирующий цвет точки
	return shadedColor;
}