#include "ModelMaterial.h"
ModelMaterial::ModelMaterial()
{
}

Material& ModelMaterial::GetMaterial()
{
	return m_material;
}

Material const& ModelMaterial::GetMaterial()const
{
	return m_material;
}

TextureMap& ModelMaterial::AddTextureMap1(GLuint texture)
{
	m_textureMap1.AttachTexture(texture);
	return m_textureMap1;
}

bool ModelMaterial::HasTextureMap1()const
{
	return m_textureMap1.IsLoaded();
}

TextureMap& ModelMaterial::GetTextureMap1()
{
	return m_textureMap1;
}

TextureMap const& ModelMaterial::GetTextureMap1()const
{
	return m_textureMap1;
}