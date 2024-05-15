#pragma once
#include "pch.h"
#include "BoundingBox.h"

class Mesh
{


public:
	Mesh(
		unsigned int vertexBufferOffset,
		unsigned int indexBufferOffset,
		unsigned vertexCount,
		unsigned indexCount,
		bool hasTextureCoords,
		BoundingBox const& boundingBox,
		GLenum primitiveType,
		GLenum indexType
	);

	struct SubMesh
	{
		unsigned startIndex;
		unsigned indexCount;
	};

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	bool HasTextureCoords() const;
	unsigned GetVertexBufferOffset() const;
	unsigned GetIndexBufferOffset() const;
	unsigned GetIndexCount() const;
	unsigned GetVertexCount() const;
	BoundingBox const& GetBoundingBox() const;
	GLenum GetPrimitiveType() const;
	GLenum GetIndexType() const;


	unsigned AddSubMesh(unsigned startIndex, unsigned subMeshIndexCount);
	unsigned GetSubMeshCount()const;
	SubMesh GetSubMesh(unsigned index)const;
	void SetMaterialSubMesh(int materialIndex, unsigned subMeshIndex);
	int GetMaterialSubMesh(int materialIndex)const;
	unsigned GetMaterialsCount()const;
	int GetMaterial(unsigned index)const;
	unsigned GetIndexSize()const;

private:
	unsigned m_vertexBufferOffset;
	unsigned m_indexBufferOffset;
	unsigned m_vertexCount;
	unsigned m_indexCount;

	bool m_hasTexture;
	BoundingBox const m_boundingBox;
	GLenum m_primitiveType;
	GLenum m_indexType;

	std::vector<SubMesh> m_subMeshes;
	std::vector<int> m_materials;
	std::vector<int> m_materialSubMesh;

};