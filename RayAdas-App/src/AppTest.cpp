#include "RayAdas.h"
#include "Main.h"
#include "AppTest.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AppTest::AppTest()
	: Layer("AppTest"), m_CameraController(1280.0f / 720.0f)
{
}

void AppTest::OnAttach()
{
	RA_PROFILE_FUNCTION();
	m_CheckerboardTexture = RayAdas::Texture2D::Create("resources/textures/haruluya.jpg");
}

void AppTest::OnDetach()
{
	RA_PROFILE_FUNCTION();
}

void AppTest::OnUpdate(RayAdas::Timestep ts)
{
	RA_PROFILE_FUNCTION();

	// Update
	{
		RA_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		RA_PROFILE_SCOPE("Renderer Prep");
		RayAdas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RayAdas::RenderCommand::Clear();
	}

	{
		RA_PROFILE_SCOPE("Renderer Draw");
		RayAdas::RenderUtils::BeginScene(m_CameraController.GetCamera());
		RayAdas::RenderUtils::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		RayAdas::RenderUtils::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		RayAdas::RenderUtils::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		RayAdas::RenderUtils::EndScene();
	}
}

void AppTest::OnImGuiRender()
{
	RA_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void AppTest::OnEvent(RayAdas::Event& e)
{
	m_CameraController.OnEvent(e);
}