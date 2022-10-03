#include "FBPlayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>


namespace Firebird {

	FBPlayer::FBPlayer()
	{
		// Smoke
		m_SmokeParticle.Position = { 0.0f, 0.0f };
		m_SmokeParticle.Velocity = { -3.0f, 0.0f }, m_SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
		m_SmokeParticle.SizeBegin = 0.35f, m_SmokeParticle.SizeEnd = 0.0f, m_SmokeParticle.SizeVariation = 0.15f;
		m_SmokeParticle.ColorBegin = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_SmokeParticle.ColorEnd = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_SmokeParticle.LifeTime = 8.0f;

		// Flames
		m_EngineParticle.Position = { 0.0f, 0.0f };
		m_EngineParticle.Velocity = { -2.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
		m_EngineParticle.SizeBegin = 0.5f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
		m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
		m_EngineParticle.LifeTime = 1.0f;
	}

	void FBPlayer::LoadAssets()
	{

		if (m_changeChar) {
			RA_INFO("Character: {0}", character);
			switch (character)
			{
			case RUI:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/rui.png");
				break;
			case HAILA:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/haila.png");
				break;
			case LUOZU:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/luozu.png");
				break;
			case MIYA:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/miya.png");
				break;
			case NUOYA:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/nuoya.png");
				break;
			case TANGXIN:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/tangxin.png");
				break;
			default:
				m_ShipTexture = RayAdas::Texture2D::Create("resources/textures/rui.png");
				break;
			}
		}
		m_changeChar = false;
	}

	void FBPlayer::OnUpdate(RayAdas::Timestep ts)
	{
		m_Time += ts;


		// simple physic.
		if (RayAdas::Input::IsKeyPressed(RA_KEY_SPACE))
		{
			m_Velocity.y += m_EnginePower;
			if (m_Velocity.y < 0.0f)
				m_Velocity.y += m_EnginePower * 2.0f;

			// Flames
			glm::vec2 emissionPoint = { 0.0f, -0.6f };
			float rotation = glm::radians(GetRotation());
			glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);
			m_EngineParticle.Position = m_Position + glm::vec2{ rotated.x, rotated.y };
			m_EngineParticle.Velocity.y = -m_Velocity.y * 0.2f - 0.2f;
			m_ParticleSystem.Emit(m_EngineParticle);
		}
		else
		{
			m_Velocity.y -= m_Gravity;
		}

		m_Velocity.y = glm::clamp(m_Velocity.y, -20.0f, 20.0f);
		m_Position += m_Velocity * (float)ts;

		// Particles
		if (m_Time > m_SmokeNextEmitTime)
		{
			m_SmokeParticle.Position = m_Position;
			m_ParticleSystem.Emit(m_SmokeParticle);
			m_SmokeNextEmitTime += m_SmokeEmitInterval;
		}

		m_ParticleSystem.OnUpdate(ts);
	}

	void FBPlayer::OnRender()
	{
		m_ParticleSystem.OnRender();
		RayAdas::RenderUtils::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, { 1920.0f/400.0f, 1200.0/400.0f }, glm::radians(GetRotation()), m_ShipTexture);
	}

	void FBPlayer::OnImGuiRender()
	{
		ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
		ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);
		int CharChoose = -1;
		ImGui::Text("Choose character:");
		ImGui::RadioButton(u8"海拉", &CharChoose, HAILA); ImGui::SameLine();
		ImGui::RadioButton(u8"罗阻", &CharChoose, LUOZU); ImGui::SameLine();
		ImGui::RadioButton(u8"瑞", &CharChoose, RUI); ImGui::SameLine();
		ImGui::RadioButton(u8"糖心", &CharChoose, TANGXIN); ImGui::SameLine();
		ImGui::RadioButton(u8"米雅", &CharChoose, MIYA); ImGui::SameLine();
		ImGui::RadioButton(u8"诺亚", &CharChoose, NUOYA); ImGui::SameLine();


		
		if (CharChoose != -1) {
			character = static_cast<PlayerType>(CharChoose);
			m_changeChar = true;
		}
	}

	void FBPlayer::Reset()
	{
		m_Position = { -10.0f, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
	}
	void FBPlayer::Resurge()
	{
		m_Position = { m_Position.x, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
	}
}