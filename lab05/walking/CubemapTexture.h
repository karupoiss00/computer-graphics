#pragma once
#include <string>
#include <map>
#include "pch.h"
#include "TextureLoader.h"

enum class CubeSide
{
    POSITIVE_X,
    NEGATIVE_X,
    POSITIVE_Y,
    NEGATIVE_Y,
    POSITIVE_Z,
    NEGATIVE_Z,
};

class CubemapTexture
{
public:

    CubemapTexture(
        std::wstring const& directory,
        std::wstring const& posXFilename,
        std::wstring const& negXFilename,
        std::wstring const& posYFilename,
        std::wstring const& negYFilename,
        std::wstring const& posZFilename,
        std::wstring const& negZFilename
    );

    ~CubemapTexture();

    void Load() const;

    void Bind(CubeSide side) const;

private:
    std::map<CubeSide, std::wstring> m_fileNamesMap;
    mutable std::map<CubeSide, GLuint> m_textureObjectsMap;

    mutable TextureLoader m_textureLoader;
};