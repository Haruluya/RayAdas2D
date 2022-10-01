#include "RApch.h"
#include "RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace RayAdas {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}