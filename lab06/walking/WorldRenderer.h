#pragma once
#include "pch.h"
#include "Column.h"
#include "Renderable.h"
#include "World.h"
#include "TextureLoader.h"

class WorldRenderer : public IRenderable
{
public:
	WorldRenderer(World& world);
	void Render() const;
	~WorldRenderer();
private:
	void LoadTextures() const;
	void UnloadTextures() const;

	void DrawSquare(size_t x, size_t z) const;
	void DrawColumn(size_t x, size_t z) const;
	void DrawMarker() const;

	World& m_world;
	TextureLoader m_textureLoader;


	mutable std::map<MaterialType, GLuint> m_textureMap;
};