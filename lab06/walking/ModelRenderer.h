#pragma once
#include "Model.h"

class ModelRenderer
{
public:
	ModelRenderer() = default;

	void RenderModel(Model const& model);

	ModelRenderer(const ModelRenderer&) = delete;
	ModelRenderer& operator=(const ModelRenderer&) = delete;
};