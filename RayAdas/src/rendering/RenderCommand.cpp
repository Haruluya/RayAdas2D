#include "RApch.h"
#include "RenderCommand.h"

#include "opengl/OpenGLRendererAPI.h"

namespace RayAdas {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}