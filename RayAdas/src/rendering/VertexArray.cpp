#include "RApch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "platform/opengl/OpenGLVertexArray.h"

namespace RayAdas {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		//case RendererAPI::None:    RA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		case RendererAPI::API::None:    RA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		RA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}