#pragma once

#include "RayAdas.h"

namespace RayAdasEditor {

	class EditorLayer : public RayAdas::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(RayAdas::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(RayAdas::Event& e) override;
	private:
		RayAdas::OrthographicCameraController m_CameraController;

		// Temp
		RayAdas::SRef<RayAdas::VertexArray> m_SquareVA;
		RayAdas::SRef<RayAdas::Shader> m_FlatColorShader;
		RayAdas::SRef<RayAdas::Framebuffer> m_Framebuffer;

		RayAdas::SRef<RayAdas::Texture2D> m_CheckerboardTexture;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}