#pragma once
#include <memory>
#include <map>
#include "pch.h"
#include "BoundingBox.h"
#include "Mesh.h"
#include "Texture.h"
#include "ModelMaterial.h"
#include "Buffer.h"

class Model
{
public:
	Model(void);

	Mesh const& GetMesh(size_t index) const;
	size_t GetMeshCount() const;

	Mesh& AddMesh(unsigned int vertexBufferOffset,
		unsigned int indexBufferOffset,
		unsigned vertexCount,
		unsigned indexCount,
		bool hasTexture,
		BoundingBox const& boundingBox,
		GLenum primitiveType,
		GLenum indexType
	);

	ModelMaterial& AddMaterial();
	CTexture2D& AddTextureImage(std::string const& name);
	bool HasTexture(std::string const& name) const;
	BoundingBox const GetBoundingBox() const;
	size_t GetTexturesCount()const;
	std::string GetTextureName(size_t index)const;
	CTexture2D& GetTextureByName(std::string const& name);
	CTexture2D const& GetTextureByName(std::string const& name) const;
	CTexture2D& GetTexture(size_t index);
	CTexture2D const& GetTexture(size_t index) const;
	size_t GetMeterialCount()const;
	ModelMaterial const& GetMaterial(size_t index) const;
	ModelMaterial& GetMaterial(size_t index);
	CVertexBuffer& GetVertexBuffer();
	CVertexBuffer const& GetVertexBuffer() const;
	CIndexBuffer& GetIndexBuffer();
	CIndexBuffer const& GetIndexBuffer() const;
private:
	// Функтор для сравнения имен текстур без учета регистра символов
	class CompareTextureNames
	{
	public:
		bool operator()(
			std::string const& textureName1,
			std::string const& textureName2) const;
	};
private:
	using CModelMaterialPtr = std::shared_ptr<ModelMaterial>;
	using CTexture2DPtr = std::shared_ptr<CTexture2D>;
	using CTextures = std::map<std::string, CTexture2DPtr, CompareTextureNames>;
	using CTextureNames = std::vector<std::string>;
	using CMeshPtr = std::shared_ptr<Mesh>;

	CVertexBuffer m_vertexBuffer;
	CIndexBuffer m_indexBuffer;

	std::vector<CModelMaterialPtr> m_materials;
	std::vector<CMeshPtr> m_meshes;

	CTextures m_textures;
	CTextureNames m_textureNames;

	mutable bool m_boundingBoxMustBeUpdated;
	mutable BoundingBox m_boundingBox;
};