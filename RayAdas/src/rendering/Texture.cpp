#include "RApch.h"
#include "Texture.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLTexture.h"
#include "stb_image/stb_image.h"

namespace RayAdas{
	SRef<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		RA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}