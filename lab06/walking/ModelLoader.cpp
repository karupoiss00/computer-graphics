#include "TextureLoader.h"
#include "ModelLoader.h"

ModelLoader::ModelLoader()
	: m_ignoreMissingTextures(true)
	, m_vertexBufferUsage(GL_STATIC_DRAW)
	, m_indexBufferUsage(GL_STATIC_DRAW)
{

}

void ModelLoader::Load3dsFile(const char* fileName, Model& model)
{
	CFile3ds file(fileName);

	std::string filePath = fileName;

	size_t slashPos = filePath.find_last_of("/\\");
	std::string fileFolder =(slashPos == std::string::npos)
		? "" 
		: filePath.substr(0, slashPos + 1);

	LoadMaterials(file.GetFile(), model, fileFolder);

	LoadMeshes(file.GetFile(), model);
}

void ModelLoader::LoadMaterials(
	Lib3dsFile const& file,
	Model& model,
	std::string const& baseFolder
)
{
	const int materialsCount = file.nmaterials;
	for (int i = 0; i < materialsCount; ++i)
	{
		Lib3dsMaterial const* pMaterial = file.materials[i];
		ModelMaterial& material = model.AddMaterial();
		Material& materialInfo = material.GetMaterial();
		{
			const float* ambient = pMaterial->ambient;
			materialInfo.SetAmbient(ambient[0], ambient[1], ambient[2]);
		}
		{
			const float* diffuse = pMaterial->diffuse;
			materialInfo.SetDiffuse(diffuse[0], diffuse[1], diffuse[2]);
		}
		{
			const float* specular = pMaterial->specular;
			materialInfo.SetSpecular(specular[0], specular[1], specular[2]);
			materialInfo.SetShininess(pMaterial->shininess);
		}
		LoadMaterialTextures(*pMaterial, model, material, baseFolder);
	}
}

void ModelLoader::LoadMaterialTextures(
	Lib3dsMaterial const& materialInfo,
	Model& model,
	ModelMaterial& material,
	std::string const& baseFolder
)
{
	Lib3dsTextureMap const& tex1 = materialInfo.texture1_map;
	if (*tex1.name)
	{
		try
		{
			CTexture2DHandle texture1 = LoadTexture(tex1.name, model, baseFolder);
			TextureMap& textureMap1 = material.AddTextureMap1(texture1);
			InitTextureMap(tex1, textureMap1);
		}
		catch (std::runtime_error const&)
		{
			if (!m_ignoreMissingTextures)
			{
				throw;
			}
		}
	}
}

GLuint ModelLoader::LoadTexture(
	std::string const& name, Model& model, std::string const& baseFolder)
{
	CTexture2D& texture = model.AddTextureImage(name);
	if (!texture)
	{
		TextureLoader loader;
		std::string textureFilePath = baseFolder + name;
		texture.Attach(
			loader.LoadTexture2D(
				std::wstring(textureFilePath.begin(),
					textureFilePath.end())
			)
		);
	}
	return texture;
}

void ModelLoader::InitTextureMap(Lib3dsTextureMap const& textureMapInfo, TextureMap& textureMap)
{
	textureMap.SetOffset(textureMapInfo.offset[0], textureMapInfo.offset[1]);
	textureMap.SetScale(textureMapInfo.scale[0], textureMapInfo.scale[1]);
	textureMap.SetRotation(textureMapInfo.rotation);
}

void ModelLoader::SetVertexBufferUsage(GLenum vertexBufferUsage)
{
	m_vertexBufferUsage = vertexBufferUsage;
}

void ModelLoader::SetIndexBufferUsage(GLenum indexBufferUsage)
{
	m_indexBufferUsage = indexBufferUsage;
}

void ModelLoader::LoadMeshes(Lib3dsFile const& file, Model& model)
{
	std::vector<unsigned char> vertexBufferData;
	std::vector<unsigned short> indexBufferData;
	const int meshCount = file.nmeshes;
	for (int i = 0; i < meshCount; ++i)
	{
		Lib3dsMesh const& mesh = *file.meshes[i];
		LoadMesh(mesh, model, vertexBufferData, indexBufferData);
	}
	model.GetVertexBuffer().Create();
	model.GetVertexBuffer().BufferData(
		vertexBufferData.size() * sizeof(vertexBufferData[0]),
		&vertexBufferData[0],
		m_vertexBufferUsage);
	model.GetIndexBuffer().Create();
	model.GetIndexBuffer().BufferData(
		indexBufferData.size() * sizeof(indexBufferData[0]),
		&indexBufferData[0],
		m_indexBufferUsage);
}

void ModelLoader::LoadMesh(
	Lib3dsMesh const& mesh,
	Model& model,
	std::vector<unsigned char>& vertexBufferData,
	std::vector<unsigned short>& indexBufferData
)
{
	const unsigned int vertexBufferOffset =
		sizeof(unsigned char) * vertexBufferData.size();
	const unsigned int indexBufferOffset = sizeof(unsigned short) * indexBufferData.size();
	FillVertexBufferData(mesh, vertexBufferData);
	FillIndexBufferData(mesh, indexBufferData);
	float minMeshBound[3];
	float maxMeshBound[3];
	lib3ds_mesh_bounding_box(
		const_cast<Lib3dsMesh*>(&mesh),
		minMeshBound, maxMeshBound);

	BoundingBox meshBoundingBox(glm::make_vec3(&minMeshBound[0]), glm::make_vec3(&maxMeshBound[0]));

	model.AddMesh(
		vertexBufferOffset,
		indexBufferOffset,
		mesh.nvertices,
		mesh.nfaces * 3,
		mesh.texcos != NULL,
		meshBoundingBox,
		GL_TRIANGLES,
		GL_UNSIGNED_SHORT
	);
}

void ModelLoader::FillVertexBufferData(Lib3dsMesh const& mesh, std::vector<unsigned char>& vertexBufferData)
{
	const int numberOfVertices = mesh.nvertices;
	float(*pInputVertices)[3] = mesh.vertices;
	float(*pInputTexCoords)[2] = mesh.texcos;
	size_t vertexBufferOffset = vertexBufferData.size();
	if (pInputTexCoords != NULL)
	{
		vertexBufferData.resize(
			vertexBufferOffset + sizeof(TexturedVertex) * numberOfVertices);
		TexturedVertex* outputVertices =
			reinterpret_cast<TexturedVertex*>(
				&vertexBufferData[vertexBufferOffset]);

		for (int v = 0; v < numberOfVertices; ++v)
		{
			float* inputPosition = pInputVertices[v];
			float* inputTexCoord = pInputTexCoords[v];
			TexturedVertex& outputVertex = outputVertices[v];
			glm::vec3& outputPosition = outputVertex.position;
			outputPosition.x = inputPosition[0];
			outputPosition.y = inputPosition[1];
			outputPosition.z = inputPosition[2];
			outputVertex.texCoord.x = inputTexCoord[0];
			outputVertex.texCoord.y = inputTexCoord[1];
			glm::vec3& outputNormal = outputVertex.normal;
			outputNormal.x = outputNormal.y = outputNormal.z = 0;
		}
	}
	else
	{
		vertexBufferData.resize(
			vertexBufferOffset + sizeof(Vertex) * numberOfVertices);
		Vertex* outputVertices =
			reinterpret_cast<Vertex*>(&vertexBufferData[vertexBufferOffset]);
		for (int v = 0; v < numberOfVertices; ++v)
		{
			float* inputPosition = pInputVertices[v];
			Vertex& outputVertex = outputVertices[v];
			glm::vec3& outputPosition = outputVertex.position;
			outputPosition.x = inputPosition[0];
			outputPosition.y = inputPosition[1];
			outputPosition.z = inputPosition[2];
			glm::vec3& outputNormal = outputVertex.normal;
			outputNormal.x = outputNormal.y = outputNormal.z = 0;
		}
	}
}

void ModelLoader::FillIndexBufferData(Lib3dsMesh const& mesh, std::vector<unsigned short>& indexBufferData)
{
	const int numberOfFaces = mesh.nfaces;
	indexBufferData.reserve(indexBufferData.size() + numberOfFaces * 3);
	for (int i = 0; i < numberOfFaces; ++i)
	{
		Lib3dsFace const& inputFace = mesh.faces[i];
		unsigned short v0 = inputFace.index[0];
		//assert(v0 < mesh.nvertices);
		unsigned short v1 = inputFace.index[1];
		//assert(v1 < mesh.nvertices);
		unsigned short v2 = inputFace.index[2];
		//assert(v2 < mesh.nvertices);
		indexBufferData.push_back(v0);
		indexBufferData.push_back(v1);
		indexBufferData.push_back(v2);
	}
}