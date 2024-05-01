#pragma once
#include "pch.h"
#include "Texture.h"

class TextureMap
{
public:
	TextureMap(GLuint textureId = 0);
	~TextureMap(void);

	TextureMap(const TextureMap&) = delete;
	TextureMap& operator=(const TextureMap&) = delete;

	CTexture2DHandle const& GetTexture() const;

	void AttachTexture(GLuint textureId);
	void SetScale(float sx, float sy);
	void SetOffset(float dx, float dy);
	void SetRotation(float rotation);
	bool IsLoaded()const;
private:
	CTexture2DHandle m_texture;
	float m_sx;
	float m_sy;
	float m_dx;
	float m_dy;
	float m_rotation;
};