#pragma once
#include <string>
#include "Model.h"
#include "Vertex.h"

class ModelLoader
{
	class CFile3ds
	{
	public:
		CFile3ds(const char* fileName)
			:m_pFile(lib3ds_file_open(fileName))
		{
			if (m_pFile == NULL)
			{
				throw std::runtime_error(std::string("Unable to open ") + fileName);
			}
		}

		Lib3dsFile const& GetFile()const
		{
			return *m_pFile;
		}

		~CFile3ds()
		{
			if (m_pFile)
			{
				lib3ds_file_free(m_pFile);
			}
		}
	private:
		CFile3ds(CFile3ds const&) = delete;
		CFile3ds& operator=(CFile3ds const&) = delete;

		Lib3dsFile* m_pFile;
	};

	struct MeshFace;

	class VertexInfo;

public:
	ModelLoader();

	void Load3dsFile(const char* fileName, Model& model);
	void SetVertexBufferUsage(GLenum vertexBufferUsage);
	void SetIndexBufferUsage(GLenum indexBufferUsage);
private:
	static void LoadMesh(unsigned materialCount, Lib3dsMesh const& mesh, Model& model, std::vector<unsigned char>& vertexBufferData, std::vector<unsigned char>& indexBufferData);
	static unsigned FillVertexBufferData(
		Lib3dsMesh const& mesh, 
		std::vector<unsigned char>& vertexBufferData,
		std::vector<MeshFace>& outputFaces
	);
	template <typename IndexType>
	static unsigned FillIndexBufferData(
		std::vector<MeshFace> const& faces,
		std::vector< std::vector<unsigned> > const& materialFaces,
		std::vector<unsigned char>& indexBufferData);

	static void SplitVerticesBySmoothGroup(Lib3dsMesh const& mesh, std::vector<VertexInfo>& outputVertices, std::vector<MeshFace>& outputFaces);
	static void BuildMaterialFacesList(unsigned meshMaterialCount, std::vector<MeshFace> const& faces, std::vector< std::vector<unsigned> >& materialFaces);

	template <class VertexType>
	static unsigned SplitVerticesAndBuildNormals(
		Lib3dsMesh const& mesh,
		std::vector<unsigned char>& vertexBufferData,
		size_t vertexBufferOffset,
		std::vector<MeshFace>& outputFaces
	);


	void LoadMaterials(
		Lib3dsFile const& file,
		Model& model,
		std::string const& baseFolder = "");
	void LoadMeshes(Lib3dsFile const& file, Model& model);
	void LoadMaterialTextures(
		Lib3dsMaterial const& materialInfo,
		Model& model,
		ModelMaterial& material,
		std::string const& baseFolder = ""
	);
	GLuint LoadTexture(
		std::string const& name,
		Model& model,
		std::string const& baseFolder = ""
	);
	void InitTextureMap(
		Lib3dsTextureMap const& textureMapInfo,
		TextureMap& textureMap
	);
	bool m_ignoreMissingTextures;
	GLenum m_vertexBufferUsage;
	GLenum m_indexBufferUsage;
};

struct ModelLoader::MeshFace
{
	unsigned vertices[3];
	int materialIndex;

};

class ModelLoader::VertexInfo
{
public:
	VertexInfo()
		: m_originalVertexIndex(-1)
		, m_derivedVertexIndex(-1)
		, m_normalIsDefined(false)
	{}

    VertexInfo(glm::vec3 const& normal, int originalVertexIndex)
		: m_originalVertexIndex(originalVertexIndex)
		, m_derivedVertexIndex(-1)
		, m_normalIsDefined(true)
		, m_normal(normal)
	{
		assert(originalVertexIndex >= 0);
	}

	glm::vec3 const& GetNormal()const
	{
		assert(NormalIsDefined());
		return m_normal;
	}

	void SetNormal(glm::vec3 const& normal)
	{
		assert(!m_normalIsDefined);
		m_normal = normal;
		m_normalIsDefined = true;
	}

	bool NormalIsDefined() const
	{
		return m_normalIsDefined;
	}

	int GetOriginalVertexIndex() const
	{
		return m_originalVertexIndex;
	}

	int GetDerivedVertex() const
	{
		return m_derivedVertexIndex;
	}

	void DeriveVertex(int vertexIndex)
	{
		assert(vertexIndex >= 0);
		assert(m_derivedVertexIndex == -1);
		m_derivedVertexIndex = vertexIndex;
	}

private:
	int m_originalVertexIndex;
	int m_derivedVertexIndex;
	bool m_normalIsDefined;		
	glm::vec3 m_normal;
};