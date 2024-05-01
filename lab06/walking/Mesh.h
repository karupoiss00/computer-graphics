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

private:
	unsigned m_vertexBufferOffset;
	unsigned m_indexBufferOffset;
	unsigned m_vertexCount;
	unsigned m_indexCount;

	bool m_hasTexture;
	BoundingBox const m_boundingBox;
	GLenum m_primitiveType;
	GLenum m_indexType;
};