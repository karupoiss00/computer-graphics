#include "Model.h"

Model::Model(void)
	: m_boundingBoxMustBeUpdated(true)
{

}

ModelMaterial& Model::AddMaterial()
{
	CModelMaterialPtr pMaterial(new ModelMaterial());
	m_materials.push_back(pMaterial);
	return *pMaterial;
}

CTexture2D& Model::AddTextureImage(std::string const& name)
{
	CTextures::iterator it = m_textures.find(name);
	if (it != m_textures.end())
	{
		return *it->second;
	}
	CTexture2DPtr pTexture(new CTexture2D());
	m_textures.insert(CTextures::value_type(name, pTexture));
	m_textureNames.push_back(name);
	return *pTexture;
}

size_t Model::GetMeterialCount()const
{
	return m_materials.size();
}

ModelMaterial const& Model::GetMaterial(size_t index)const
{
	return *m_materials.at(index);
}

ModelMaterial& Model::GetMaterial(size_t index)
{
	return *m_materials.at(index);
}

bool Model::HasTexture(std::string const& name) const
{
	auto it = m_textures.find(name);
	return it != m_textures.end();
}

size_t Model::GetTexturesCount()const
{
	return m_textures.size();
}

std::string Model::GetTextureName(size_t index)const
{
	return m_textureNames.at(index);
}

CTexture2D& Model::GetTextureByName(std::string const& name)
{
	CTextures::iterator it = m_textures.find(name);
	if (it == m_textures.end())
	{
		throw std::logic_error("Texture with the specified name does not exist");
	}
	return *it->second;
}

CTexture2D const& Model::GetTextureByName(std::string const& name)const
{
	CTextures::const_iterator it = m_textures.find(name);
	if (it == m_textures.end())
	{
		throw std::logic_error("Texture with the specified name does not exist");
	}
	return *it->second;
}

CTexture2D& Model::GetTexture(size_t index)
{
	std::string textureName = m_textureNames.at(index);
	return GetTextureByName(textureName);
}

CTexture2D const& Model::GetTexture(size_t index)const
{
	std::string textureName = m_textureNames.at(index);
	return GetTextureByName(textureName);
}

bool Model::CompareTextureNames::operator()(std::string const& textureName1, std::string const& textureName2) const
{
	std::string name1LowerCase(textureName1);
	std::transform(
		name1LowerCase.begin(),
		name1LowerCase.end(),
		name1LowerCase.begin(),
		tolower);
	std::string name2LowerCase(textureName2);
	std::transform(
		name2LowerCase.begin(),
		name2LowerCase.end(),
		name2LowerCase.begin(),
		tolower);
	return name1LowerCase < name2LowerCase;
}

Mesh& Model::AddMesh(
	unsigned vertexBufferOffset,
	unsigned indexBufferOffset,
	unsigned vertexCount,
	unsigned indexCount,
	bool hasTexture,
	BoundingBox const& boundingBox,
	GLenum primitiveType,
	GLenum indexType
)
{
	CMeshPtr pMesh(new Mesh(
		vertexBufferOffset,
		indexBufferOffset,
		vertexCount,
		indexCount,
		hasTexture,
		boundingBox,
		primitiveType,
		indexType
	));
	m_meshes.push_back(pMesh);
	m_boundingBoxMustBeUpdated = true;
	return *pMesh;
}

size_t Model::GetMeshCount()const
{
	return m_meshes.size();
}

Mesh const& Model::GetMesh(size_t index)const
{
	return *m_meshes.at(index);
}

BoundingBox const Model::GetBoundingBox()const
{
	if (m_boundingBoxMustBeUpdated)
	{
		BoundingBox box;
		for (size_t i = 0; i < m_meshes.size(); ++i)
		{
			box = box.Union(m_meshes[i]->GetBoundingBox());
		}
		m_boundingBox = box;
		m_boundingBoxMustBeUpdated = false;
	}

	return m_boundingBox;
}

CVertexBuffer& Model::GetVertexBuffer()
{
	return m_vertexBuffer;
}

CVertexBuffer const& Model::GetVertexBuffer()const
{
	return m_vertexBuffer;
}

CIndexBuffer& Model::GetIndexBuffer()
{
	return m_indexBuffer;
}

CIndexBuffer const& Model::GetIndexBuffer()const
{
	return m_indexBuffer;
}