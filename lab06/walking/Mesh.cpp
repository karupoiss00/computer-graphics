#include "Mesh.h"

Mesh::Mesh(
	unsigned int vertexBufferOffset,
	unsigned int indexBufferOffset,
	unsigned vertexCount,
	unsigned indexCount,
	bool hasTexture,
	BoundingBox const& boundingBox,
	GLenum primitiveType,
	GLenum indexType
)
	: m_indexBufferOffset(indexBufferOffset)
	, m_vertexBufferOffset(vertexBufferOffset)
	, m_vertexCount(vertexCount)
	, m_indexCount(indexCount)
	, m_hasTexture(hasTexture)
	, m_boundingBox(boundingBox)
	, m_primitiveType(primitiveType)
	, m_indexType(indexType)
{}

bool Mesh::HasTextureCoords()const
{
	return m_hasTexture;
}

unsigned Mesh::GetVertexBufferOffset()const
{
	return m_vertexBufferOffset;
}

unsigned Mesh::GetIndexBufferOffset()const
{
	return m_indexBufferOffset;
}

unsigned Mesh::GetIndexCount()const
{
	return m_indexCount;
}

BoundingBox const& Mesh::GetBoundingBox()const
{
	return m_boundingBox;
}

GLenum Mesh::GetPrimitiveType()const
{
	return m_primitiveType;
}

GLenum Mesh::GetIndexType()const
{
	return m_indexType;
}

unsigned int Mesh::GetVertexCount()const
{
	return m_vertexCount;
}

unsigned Mesh::AddSubMesh(unsigned startIndex, unsigned subMeshIndexCount)
{
	if (startIndex >= m_indexCount)
	{
		throw std::out_of_range("Start vertex index is out of range");
	}

	if (
		(subMeshIndexCount == 0) ||
		(startIndex + subMeshIndexCount < startIndex) ||
		(startIndex + subMeshIndexCount > m_indexCount)
		)
	{
		throw std::out_of_range("SubMesh index count is out of range");
	}

	SubMesh subMesh = { startIndex, subMeshIndexCount };
	m_subMeshes.push_back(subMesh);

	return m_subMeshes.size() - 1;
}

Mesh::SubMesh Mesh::GetSubMesh(unsigned index)const
{
	return m_subMeshes.at(index);
}

unsigned Mesh::GetSubMeshCount()const
{
	return m_subMeshes.size();
}

void Mesh::SetMaterialSubMesh(int materialIndex, unsigned subMeshIndex)
{
	if (subMeshIndex >= GetSubMeshCount())
	{
		throw std::out_of_range("Sub mesh index is out of range");
	}

	++materialIndex;

	if (materialIndex < 0)
	{
		throw std::out_of_range("Invalid material index");
	}

	if (static_cast<unsigned>(materialIndex) >= m_materialSubMesh.size())
	{
		m_materialSubMesh.insert(
			m_materialSubMesh.end(),
			materialIndex - m_materialSubMesh.size() + 1,
			-1);
	}

	if (m_materialSubMesh[materialIndex] >= 0)
	{
		throw std::logic_error("Material sub mesh has already specified");
	}

	m_materials.push_back(materialIndex - 1);

	m_materialSubMesh[materialIndex] = subMeshIndex;
}

int Mesh::GetMaterialSubMesh(int materialIndex) const
{
	++materialIndex;
	if (materialIndex < 0)
	{
		throw std::out_of_range("Invalid material index");
	}

	if (static_cast<unsigned>(materialIndex) >= m_materialSubMesh.size())
	{
		return -1;
	}

	return m_materialSubMesh[materialIndex];
}

unsigned Mesh::GetMaterialsCount() const
{
	return m_materials.size();
}

int Mesh::GetMaterial(unsigned index) const
{
	return m_materials.at(index);
}


unsigned Mesh::GetIndexSize() const
{
	return
		(m_indexType == GL_UNSIGNED_BYTE) ? sizeof(GLubyte) :
		(m_indexType == GL_UNSIGNED_SHORT) ? sizeof(GLshort) :
		(m_indexType == GL_UNSIGNED_INT) ? sizeof(GLuint) : 0;
}
