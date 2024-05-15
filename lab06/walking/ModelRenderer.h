#pragma once
#include "Model.h"

class ModelRenderer
{
public:
	ModelRenderer();

	void RenderModel(Model const& model);

	ModelRenderer(const ModelRenderer&) = delete;
	ModelRenderer& operator=(const ModelRenderer&) = delete;
private:
	bool RenderMaterialSubMesh(
		Model const& model,	
		unsigned meshIndex,
		int materialIndex,	
		bool activateMaterial
	) const;


	void SetupMeshVertexPointers(
		Mesh const& mesh,
		GLubyte const* pVertexBufferData 
	) const;


	void RenderSubMeshFaces(
		Mesh const& mesh,
		unsigned subMeshIndex,
		GLubyte const* pMeshIndices	
	) const;

	mutable bool m_texCoordsEnabled;
};