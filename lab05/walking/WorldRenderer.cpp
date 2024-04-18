#include "WorldRenderer.h"

std::map<MaterialType, std::wstring> TEXTURE_FILES = {
	{MaterialType::STONE, L"./res/stone.png"},
	{MaterialType::STONE_LIANE, L"./res/stone_liane.png"},
	{MaterialType::BRICK, L"./res/brick.png"},
	{MaterialType::BRICK_LIANE, L"./res/brick_liane.png"},
	{MaterialType::BRICK_CRACKED, L"./res/brick_cracked.png"},
	{MaterialType::BRICK_CHISELED, L"./res/brick_chiseled.png"},
	{MaterialType::BRICK_SMOOTHED, L"./res/brick_smoothed.png"},
	{MaterialType::MARKER, L"./res/marker.png"},
};

WorldRenderer::WorldRenderer(World& world)
	: m_world(world)
{}

WorldRenderer::~WorldRenderer()
{
	UnloadTextures();
}

void WorldRenderer::Render() const
{	
	LoadTextures();
	
	auto map = m_world.GetMap();

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			auto cell = map[i][j];
			glBindTexture(GL_TEXTURE_2D, m_textureMap.at(cell.material));
			if (cell.filled)
			{
				DrawColumn(i, j);
			}
			else
			{
				DrawSquare(i, j);
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D, m_textureMap.at(MaterialType::MARKER));
	DrawMarker();
}

void WorldRenderer::DrawSquare(int x, int z) const
{
	glPushMatrix();
	glNormal3f(0, 1, 0);
	glTranslated(x + 0.5, 0, z + 0.5);
	glScaled(0.5, 0.5, 0.5);
		
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1);
	glVertex3d(-1, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3d(-1, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3d(1, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3d(1 , 0, -1);
	glEnd();
	glPopMatrix();
}

void WorldRenderer::DrawColumn(int x, int z) const
{
	Column column({x + 0.5, 0, z + 0.5});
	column.Draw();
}


void WorldRenderer::DrawMarker() const
{
	Marker const& marker = m_world.GetMarker();
	auto markerBox = marker.GetBox();
	auto pos = marker.GetPosition();
	pos.y -= markerBox.size.y / 2;
	Column column(pos, float(markerBox.size.x), float(markerBox.size.y));
	column.Draw();
}

void WorldRenderer::LoadTextures() const
{
	if (m_textureMap.size() != 0)
	{
		return;
	}

	for (auto [materialType, fileName] : TEXTURE_FILES)
	{
		auto texture = m_textureLoader.LoadTexture2D(fileName, static_cast<GLuint>(materialType));
		m_textureMap.insert({ materialType, texture });
	}
}

void WorldRenderer::UnloadTextures() const
{
	for (auto [material, textureId] : m_textureMap)
	{
		glDeleteTextures(1, &textureId);
	}
}
