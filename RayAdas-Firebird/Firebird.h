#pragma once
#include "RayAdas.h"
#include "FBLevel.h"
#include "FirebirdConstant.h"
#include "imgui/imgui.h"

namespace Firebird {
	class FirebirdLayer : public RayAdas::Layer {
	public:
		FirebirdLayer();
		virtual ~FirebirdLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(RayAdas::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(RayAdas::Event& e) override;
		bool OnMouseButtonPressed(RayAdas::MouseButtonPressedEvent& e);
		bool OnWindowResize(RayAdas::WindowResizeEvent& e);
	private:
		void CreateCamera(uint32_t width, uint32_t height);
	private:
		RayAdas::URef<RayAdas::OrthographicCamera> m_Camera;
		FBLevel m_Level;
		ImFont* m_Font;
		float m_Time = 0.0f;
		bool m_Blink = false;
		ImU32 m_FontColor;
		GameState m_State = GameState::MainMenu;
	};
}