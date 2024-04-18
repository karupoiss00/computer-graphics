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

	void DrawSquare(int x, int z) const;
	void DrawColumn(int x, int z) const;
	void DrawMarker() const;

	World& m_world;
	CTextureLoader m_textureLoader;


	mutable std::map<MaterialType, GLuint> m_textureMap;
};