#include "RApch.h"
#include "RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace RayAdas {

	URef<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}