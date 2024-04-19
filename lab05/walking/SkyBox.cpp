#include <glm/glm.hpp>
#include "Skybox.h"

SkyBox::SkyBox(float size, CubemapTexture& texture)
	: m_texture(texture)
	, m_size(size)
	, m_position(m_size / 2, 0, m_size / 2)
{

}

void SkyBox::Render() const
{
	static constexpr float vertices[8][3] = {
		{ -1, -1, -1 },
		{ +1, -1, -1 },
		{ +1, +1, -1 }, 
		{ -1, +1, -1 }, 
		{ -1, -1, +1 },
		{ +1, -1, +1 }, 
		{ +1, +1, +1 }, 
		{ -1, +1, +1 }, 
	};
	/*
	   Y
	   |
	   |
	   |
	   +---X
	  /
	 /
	Z
	   3----2
	  /    /|
	 /    / |
	7----6  |
	|  0 |  1
	|    | /
	|    |/
	4----5
	*/
	// ћ

	static constexpr unsigned char faces[6][4] = {
		{ 7, 4, 0, 3 }, // грань x<0
		{ 2, 1, 5, 6 }, // грань x>0
		{ 5, 1, 0, 4 }, // грань y<0
		{ 3, 2, 6, 7 }, // грань y>0
		{ 3, 0, 1, 2 }, // грань z<0
		{ 6, 5, 4, 7 }, // грань z>0
	};
	static constexpr float textureCoords[4][2] = {
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 0 },	
	};
	static constexpr CubeSide sides[6] = {
		CubeSide::NEGATIVE_X,
		CubeSide::POSITIVE_X,
		CubeSide::NEGATIVE_Y,
		CubeSide::POSITIVE_Y,
		CubeSide::NEGATIVE_Z,
		CubeSide::POSITIVE_Z,
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	glPushMatrix();

	glTranslated(m_position.x, m_position.y, m_position.z);

	for (size_t face = 0; face < faceCount; ++face)
	{
		const unsigned char* facePoints = faces[face];

		auto p0 = glm::make_vec3(vertices[facePoints[0]]);
		auto p1 = glm::make_vec3(vertices[facePoints[1]]);
		auto p2 = glm::make_vec3(vertices[facePoints[2]]);
		auto p3 = glm::make_vec3(vertices[facePoints[3]]);

		p0 *= m_size * 0.5f;
		p1 *= m_size * 0.5f;
		p2 *= m_size * 0.5f;
		p3 *= m_size * 0.5f;

		auto v01 = p1 - p0;
		auto v02 = p2 - p0;
		auto normal = glm::normalize(glm::cross(v01, v02));

		m_texture.Bind(sides[face]);

		glBegin(GL_QUADS);
		{
			glNormal3fv(glm::value_ptr(normal));

			glTexCoord2fv(textureCoords[0]);
			glVertex3fv(glm::value_ptr(p0));
			glTexCoord2fv(textureCoords[1]);
			glVertex3fv(glm::value_ptr(p1));
			glTexCoord2fv(textureCoords[2]);
			glVertex3fv(glm::value_ptr(p2));
			glTexCoord2fv(textureCoords[3]);
			glVertex3fv(glm::value_ptr(p3));
		}
		glEnd();
	}

	

	glPopMatrix();
}

void SkyBox::SetPosition(glm::dvec3 position)
{
	m_position = position;
}