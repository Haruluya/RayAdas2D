#pragma once

namespace RayAdas {

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		static URef<GraphicsContext> Create(void *window);
	};

}