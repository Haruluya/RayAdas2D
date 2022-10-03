#pragma once
#include "Firebird.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace Firebird {
	FirebirdLayer::FirebirdLayer()
		: Layer("FirebirdLayer")
	{
		auto& window = RayAdas::Application::Get().GetWindow();
		CreateCamera(window.GetWidth(), window.GetHeight());

		// set random seed.
		RayAdas::Random::Init();

		m_FontColor = 0xffffffff;
	}

	void FirebirdLayer::OnAttach()
	{

		m_Level.Init();


		// set chinese font.
		ImGuiIO io = ImGui::GetIO();
		m_Font = io.Fonts->AddFontFromFileTTF("resources/fonts/font.otf", 20.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	}

	void FirebirdLayer::OnDetach()
	{
	}

	void FirebirdLayer::OnUpdate(RayAdas::Timestep ts)
	{
		m_Time += ts;

		// Blink display.
		if ((int)(m_Time * 10.0f) % 8 > 4)
			m_Blink = !m_Blink;

		// if game is over, set flag.
		if (m_Level.IsGameOver())
			m_State = GameState::GameOver;
		// set camera position.
		const auto& playerPos = m_Level.GetPlayer().GetPosition();
		m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

		// if game is over, level stop updating.
		switch (m_State)
		{
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);
			break;
		}
		}

		// Render
		RayAdas::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 0.1f });
		RayAdas::RenderCommand::Clear();

		// update martix.
		RayAdas::RenderUtils::BeginScene(*m_Camera);
		m_Level.OnRender();
		RayAdas::RenderUtils::EndScene();


	}

	void FirebirdLayer::OnImGuiRender()
	{
		ImGui::Begin("Firebird");

		ImGui::Text("A game similar to firebird in RayAdas Engine.");
		ImGui::Text("Layer:");
		ImGui::ColorEdit3("Font Color", (float*)&m_FontColor);


		m_Level.OnImGuiRender();	
		ImGui::End();
		
		switch (m_State)
		{
		case GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string(u8"当前分数: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 24.0f, ImGui::GetWindowPos(), m_FontColor, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = RayAdas::Application::Get().GetWindow().GetWidth();
			auto height = RayAdas::Application::Get().GetWindow().GetHeight();


			// set play text.
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;

			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 60.0f, pos, m_FontColor, u8"开始游戏");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = RayAdas::Application::Get().GetWindow().GetWidth();
			auto height = RayAdas::Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 60.0f, pos, m_FontColor, u8"重新开始");

			pos.x += 200.0f;
			pos.y += 150.0f;


			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string(u8"最终得分: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 24.0f, pos, m_FontColor, scoreStr.c_str());
			break;
		}
		}

	}



	void FirebirdLayer::OnEvent(RayAdas::Event& e)
	{
		RayAdas::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<RayAdas::WindowResizeEvent>(RA_BIND_EVENT_FN(FirebirdLayer::OnWindowResize));
		dispatcher.Dispatch<RayAdas::MouseButtonPressedEvent>(RA_BIND_EVENT_FN(FirebirdLayer::OnMouseButtonPressed));
	}

	bool FirebirdLayer::OnMouseButtonPressed(RayAdas::MouseButtonPressedEvent& e)
	{
		if (m_State == GameState::GameOver)
			m_Level.Reset();

		m_State = GameState::Play;
		return false;
	}

	bool FirebirdLayer::OnWindowResize(RayAdas::WindowResizeEvent& e)
	{
		CreateCamera(e.GetWidth(), e.GetHeight());
		return false;
	}

	void FirebirdLayer::CreateCamera(uint32_t width, uint32_t height)
	{
		float aspectRatio = (float)width / (float)height;

		float camWidth = 8.0f;
		float bottom = -camWidth;
		float top = camWidth;
		float left = bottom * aspectRatio;
		float right = top * aspectRatio;
		m_Camera = std::make_unique<RayAdas::OrthographicCamera>(left, right, bottom, top);
	}
}