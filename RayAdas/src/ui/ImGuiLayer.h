#pragma once

#include "layer/Layer.h"

#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"

namespace RayAdas {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void BlockEvents(bool block) { m_BlockEvents = block; }

		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}