#include "pch.h"
#include "Vertex.h"
#include "Model.h"
#include "ModelRenderer.h"

ModelRenderer::ModelRenderer()
	:m_texCoordsEnabled(false)
{
}


void ModelRenderer::RenderModel(Model const& model)
{
	const size_t meshCount = model.GetMeshCount();

	if (meshCount == 0)
	{
		return;
	}

	model.GetVertexBuffer().Bind();
	model.GetIndexBuffer().Bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	m_texCoordsEnabled = !model.GetMesh(0).HasTextureCoords();

	const int materialCount = model.GetMeterialCount();

	for (int material = -1; material < materialCount; ++material)
	{
		bool materialActivated = false;

		for (size_t mesh = 0; mesh < meshCount; ++mesh)
		{
			bool needToActivateMaterial =
				!materialActivated && material >= 0;

			materialActivated |= RenderMaterialSubMesh(
				model, mesh, material, needToActivateMaterial);
		}
	}

	if (m_texCoordsEnabled)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

bool ModelRenderer::RenderMaterialSubMesh(
	Model const& model,
	unsigned meshIndex,
	int materialIndex,
	bool activateMaterial
) const
{
	Mesh const& mesh = model.GetMesh(meshIndex);

	const int materialSubMeshIndex =
		mesh.GetMaterialSubMesh(materialIndex);

	if (materialSubMeshIndex < 0)
	{
		return false;
	}

	bool materialActivated = false;

	if (activateMaterial && (materialIndex >= 0))
	{
		ModelMaterial const& modelMaterial = model.GetMaterial(materialIndex);

		modelMaterial.GetMaterial().Activate();

		materialActivated = true;
	}

	GLubyte const* pVertexPointer = reinterpret_cast<GLubyte const*>
		(model.GetVertexBuffer().GetBufferPointer());

	SetupMeshVertexPointers(mesh, pVertexPointer);

	bool needToUnlockArrays = false;
	if (
		(mesh.GetIndexCount() > mesh.GetVertexCount() * 2) &&
		GLEW_EXT_compiled_vertex_array
		)
	{
		glLockArraysEXT(0, mesh.GetVertexCount());
		needToUnlockArrays = true;
	}

	GLubyte const* pIndexPointer = reinterpret_cast<GLubyte const*>
		(model.GetIndexBuffer().GetBufferPointer());

	RenderSubMeshFaces(
		mesh,
		materialSubMeshIndex,
		pIndexPointer + mesh.GetIndexBufferOffset());

	if (needToUnlockArrays)
	{
		glUnlockArraysEXT();
	}

	return materialActivated;
}

void ModelRenderer::SetupMeshVertexPointers(
	Mesh const& mesh,
	GLubyte const* pVertexBufferData) const
{

	unsigned vertexBufferOffset = mesh.GetVertexBufferOffset();

	bool meshUsesTexture = mesh.HasTextureCoords();

	unsigned stride = meshUsesTexture 
		? sizeof(TexturedVertex) 
		: sizeof(Vertex);

	glVertexPointer(
		3,
		GL_FLOAT,
		stride,
		pVertexBufferData + vertexBufferOffset + offsetof(Vertex, position)
	);
	glNormalPointer(
		GL_FLOAT,
		stride,
		pVertexBufferData + vertexBufferOffset + offsetof(Vertex, normal)
	);

	if (meshUsesTexture && !m_texCoordsEnabled)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else if (!meshUsesTexture && m_texCoordsEnabled)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (meshUsesTexture)
	{
		glTexCoordPointer(
			2,
			GL_FLOAT,
			stride,
			pVertexBufferData +
			vertexBufferOffset +
			offsetof(TexturedVertex, texCoord));
	}

	m_texCoordsEnabled = meshUsesTexture;
}

void ModelRenderer::RenderSubMeshFaces(
	Mesh const& mesh,
	unsigned subMeshIndex,	
	GLubyte const* pMeshIndices
) const
{
	Mesh::SubMesh const subMesh = mesh.GetSubMesh(subMeshIndex);

	GLubyte const* pSubMeshPointer =
		pMeshIndices + (subMesh.startIndex * mesh.GetIndexSize());

	if (GLEW_EXT_draw_range_elements)
	{
		glDrawRangeElements(
			mesh.GetPrimitiveType(),
			0,
			mesh.GetVertexCount() - 1,
			subMesh.indexCount,
			mesh.GetIndexType(),
			pSubMeshPointer
		);
	}
	else
	{
		glDrawElements(
			mesh.GetPrimitiveType(),
			subMesh.indexCount,
			mesh.GetIndexType(),
			pSubMeshPointer
		);
	}
}
