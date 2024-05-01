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
public:
	ModelLoader();

	void Load3dsFile(const char* fileName, Model& model);
	void SetVertexBufferUsage(GLenum vertexBufferUsage);
	void SetIndexBufferUsage(GLenum indexBufferUsage);
private:
	static void LoadMesh(Lib3dsMesh const& mesh, Model& model, std::vector<unsigned char>& vertexBufferData, std::vector<unsigned short>& indexBufferData);
	static void FillVertexBufferData(Lib3dsMesh const& mesh, std::vector<unsigned char>& vertexBufferData);
	static void FillIndexBufferData(Lib3dsMesh const& mesh, std::vector<unsigned short>& indexBufferData);

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

