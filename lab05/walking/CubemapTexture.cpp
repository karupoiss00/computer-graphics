#include "CubemapTexture.h"
#ifndef GL_CLAMP_TO_EDGE_EXT
#define GL_CLAMP_TO_EDGE_EXT 0x812F
#endif

CubemapTexture::CubemapTexture(
    std::wstring const& directory,
    std::wstring const& posXFilename,
    std::wstring const& negXFilename,
    std::wstring const& posYFilename,
    std::wstring const& negYFilename,
    std::wstring const& posZFilename,
    std::wstring const& negZFilename
)
{
    m_fileNamesMap = {
        {CubeSide::POSITIVE_X, directory + posXFilename},
        {CubeSide::NEGATIVE_X, directory + negXFilename},
        {CubeSide::POSITIVE_Y, directory + posYFilename},
        {CubeSide::NEGATIVE_Y, directory + negYFilename},
        {CubeSide::POSITIVE_Z, directory + posZFilename},
        {CubeSide::NEGATIVE_Z, directory + negZFilename}
    };
}

CubemapTexture::~CubemapTexture()
{
    for (auto [_, textureObj] : m_textureObjectsMap)
    {
        glDeleteTextures(1, &textureObj);
    }
}

void CubemapTexture::Load() const
{
    if (!m_textureObjectsMap.empty())
    {
        return;
    }

    m_textureLoader.SetWrapMode(GL_CLAMP_TO_EDGE_EXT, GL_CLAMP_TO_EDGE_EXT);

    for (auto [side, filePath] : m_fileNamesMap)
    {
        GLuint textureObj;
        glGenTextures(1, &textureObj);
        m_textureLoader.LoadTexture2D(filePath, textureObj);
        m_textureObjectsMap.insert({ side, textureObj});
    }
}

void CubemapTexture::Bind(CubeSide side) const
{
    if (m_textureObjectsMap.empty())
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_textureObjectsMap[side]);
}