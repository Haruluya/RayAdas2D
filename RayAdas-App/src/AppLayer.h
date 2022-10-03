#pragma once

#include "RayAdas.h"

namespace RayAdasApp {
	class AppLayer : public RayAdas::Layer
	{
	public:
		AppLayer();
		virtual ~AppLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(RayAdas::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(RayAdas::Event& e) override;
	private:
		RayAdas::ShaderLibrary m_ShaderLibrary;
		RayAdas::SRef<RayAdas::Shader> m_Shader;
		RayAdas::SRef<RayAdas::VertexArray> m_VertexArray;

		RayAdas::SRef<RayAdas::Shader> m_FlatColorShader;
		RayAdas::SRef<RayAdas::VertexArray> m_SquareVA;

		RayAdas::SRef<RayAdas::Texture2D> m_Texture, m_ChernoLogoTexture;

		RayAdas::OrthographicCameraController m_CameraController;
		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	};
}
