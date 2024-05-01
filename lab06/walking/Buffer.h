#pragma once
#include <vector>
#include "BufferObject.h"

template<GLenum target>
class CBufferImpl
{
public:
	CBufferImpl(bool useVBO = true)
		: m_hasData(false)
		, m_useVBO(useVBO)
		, m_created(false)
	{
	}

	~CBufferImpl()
	{
		UpdateCurrentBufferPointer(false, NULL);
	}

	void Create()
	{
		if (!m_created)
		{
			m_useVBO = m_useVBO && (GLEW_ARB_vertex_buffer_object == GL_TRUE);

			if (m_useVBO && (m_buffer == 0))
			{
				m_buffer.Create();
			}

			m_created = true;
		}
	}

	void Bind() const
	{
		if (!m_created)
		{
			throw std::logic_error("The buffer has not been created");
		}

		if (m_useVBO)
		{
			m_buffer.Bind();
		}
		else if (GLEW_ARB_vertex_buffer_object)
		{
			glBindBuffer(target, 0);
		}

		UpdateCurrentBufferPointer(false, this);
	}

	static void Unbind()
	{
		if (GLEW_ARB_vertex_buffer_object)
		{
			glBindBuffer(target, 0);
		}

		UpdateCurrentBufferPointer(false, NULL);
	}

	void BufferData(GLsizeiptr size, GLvoid const* data, GLenum usage)
	{
		UpdateCurrentBufferPointer(true, this);

		if (m_useVBO)
		{
			m_buffer.BufferData(size, data, usage);
		}
		else
		{
			if (data != NULL)
			{
				GLubyte const* pDataStart = reinterpret_cast<GLubyte const*>(data);
				GLubyte const* pDataEnd = pDataStart + size;
				m_data.assign(pDataStart, pDataEnd);
			}
			else
			{
				auto empty = std::vector<GLubyte>();
				m_data.swap(empty);
			}
		}
		m_hasData = (data != NULL);
	}

	GLvoid const* GetBufferPointer()const
	{
		if (!m_hasData)
		{
			throw std::logic_error("The buffer contains no data");
		}

		UpdateCurrentBufferPointer(true, this);
		if (m_useVBO)
		{
			return NULL;
		}
		else
		{
			return &m_data[0];
		}
	}

private:
	static void UpdateCurrentBufferPointer(bool callBind, CBufferImpl const* thisPtr)
	{
		static const CBufferImpl* pCurrentBuffer = NULL;
		if (pCurrentBuffer != thisPtr)
		{
			pCurrentBuffer = thisPtr;
			if (callBind && (thisPtr != NULL))
			{
				thisPtr->Bind();
			}
		}
	}

	CBufferImpl(CBufferImpl const&) = delete;
	CBufferImpl& operator=(CBufferImpl const&) = delete;
	CBufferObjectImpl<true, target> m_buffer;
	std::vector<GLubyte> m_data;
	bool m_hasData;
	bool m_useVBO;
	bool m_created;
};

using CVertexBuffer = CBufferImpl<GL_ARRAY_BUFFER>;
using CIndexBuffer = CBufferImpl<GL_ELEMENT_ARRAY_BUFFER>;