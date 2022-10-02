#include "RApch.h"
#include "OpenGLVertexArray.h"

#include<glad/glad.h>

namespace RayAdas {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case RayAdas::ShaderDataType::Float:    return GL_FLOAT;
		case RayAdas::ShaderDataType::Float2:   return GL_FLOAT;
		case RayAdas::ShaderDataType::Float3:   return GL_FLOAT;
		case RayAdas::ShaderDataType::Float4:   return GL_FLOAT;
		case RayAdas::ShaderDataType::Mat3:     return GL_FLOAT;
		case RayAdas::ShaderDataType::Mat4:     return GL_FLOAT;
		case RayAdas::ShaderDataType::Int:      return GL_INT;
		case RayAdas::ShaderDataType::Int2:     return GL_INT;
		case RayAdas::ShaderDataType::Int3:     return GL_INT;
		case RayAdas::ShaderDataType::Int4:     return GL_INT;
		case RayAdas::ShaderDataType::Bool:     return GL_BOOL;
		}

		RA_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		RA_PROFILE_FUNCTION();
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		RA_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		RA_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		RA_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		RA_PROFILE_FUNCTION();
		RA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		RA_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}