#pragma once
#include "pch.h"

class CBaseTexture
{
public:
	void Create()
	{
		assert(!m_texture);
		glGenTextures(1, &m_texture);
	}

	void Delete()
	{
		assert(m_texture);
		glDeleteTextures(1, &m_texture);
		m_texture = 0;
	}

	GLuint Detach()
	{
		GLuint texture = m_texture;
		m_texture = 0;
		return texture;
	}

	operator GLuint() const
	{
		return m_texture;
	}

	void BindTo(GLenum target) const
	{
		assert(m_texture != 0);
		glBindTexture(target, m_texture);
	}

protected:
	CBaseTexture(GLuint texture)
		: m_texture(texture)
	{
	}

	void SetTexture(GLuint texture)
	{
		m_texture = texture;
	}

private:
	GLuint m_texture;

private:
	CBaseTexture(CBaseTexture const&);
	CBaseTexture& operator=(CBaseTexture const&);
};

template <bool t_managed, class TBase>
class CTextureImpl : public TBase
{
public:
	CTextureImpl(GLuint texture = 0)
		: TBase(texture)
	{
	}

	~CTextureImpl()
	{
		bool m = t_managed;
		if (m && (*this != 0))
		{
			TBase::Delete();
		}
	}

	CTextureImpl& operator=(GLuint texture)
	{
		Attach(texture);
		return *this;
	}

	void Attach(GLuint texture)
	{
		if (t_managed && (*this != 0) && (texture != *this))
		{
			TBase::Delete();
		}
		TBase::SetTexture(texture);
	}
};

class CTexture2DImpl : public CBaseTexture
{
public:
	CTexture2DImpl(GLuint texture = 0)
		: CBaseTexture(texture)
	{
	}

	void Bind() const
	{
		BindTo(GL_TEXTURE_2D);
	}

	static void TexImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
	{
		glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, pixels);
	}
};

class CTexture1DImpl : public CBaseTexture
{
public:
	CTexture1DImpl(GLuint texture = 0)
		: CBaseTexture(texture)
	{
	}

	virtual void Bind() const
	{
		BindTo(GL_TEXTURE_1D);
	}

	static void TexImage(GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
	{
		glTexImage1D(GL_TEXTURE_1D, level, internalFormat, width, border, format, type, pixels);
	}
};

using CTexture = CTextureImpl<true, CBaseTexture>;
using CTextureHandle =  CTextureImpl<false, CBaseTexture>;

using CTexture2D = CTextureImpl<true, CTexture2DImpl>;
using CTexture2DHandle = CTextureImpl<false, CTexture2DImpl>;

using CTexture1D = CTextureImpl<true, CTexture1DImpl>;
using CTexture1DHandle = CTextureImpl<false, CTexture1DImpl>;