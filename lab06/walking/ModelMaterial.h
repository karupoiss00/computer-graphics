#pragma once
#include "pch.h"
#include "Material.h"
#include "TextureMap.h"

class ModelMaterial
{
public:
	ModelMaterial();

	ModelMaterial(const ModelMaterial&) = delete;
	ModelMaterial& operator=(const ModelMaterial&) = delete;

	TextureMap& AddTextureMap1(GLuint texture);
	bool HasTextureMap1()const;
	TextureMap const& GetTextureMap1()const;
	TextureMap& GetTextureMap1();
	Material& GetMaterial();
	Material const& GetMaterial()const;
private:
	TextureMap m_textureMap1;
	Material m_material;
};