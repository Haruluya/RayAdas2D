#pragma once

#include <RayAdas.h>

namespace Firebird {
	enum PlayerType {
		HAILA, LUOZU, MIYA, NUOYA, RUI, TANGXIN
	};
	class FBPlayer
	{
	public:
		FBPlayer();

		void LoadAssets();

		void OnUpdate(RayAdas::Timestep ts);
		void OnRender();

		void OnImGuiRender();

		void Reset();
		void Resurge();
		float GetRotation() { return m_Velocity.y * 4.0f - 90.0f; }
		const glm::vec2& GetPosition() const { return m_Position; }

		uint32_t GetScore() const { return (uint32_t)(m_Position.x + 10.0f); }
	private:
		glm::vec2 m_Position = { -10.0f, 0.0f };
		glm::vec2 m_Velocity = { 5.0f, 0.0f };

		float m_EnginePower = 0.5f;
		float m_Gravity = 0.4f;
		bool m_changeChar = true;
		float m_Time = 0.0f;
		float m_SmokeEmitInterval = 0.4f;
		float m_SmokeNextEmitTime = m_SmokeEmitInterval;
		

		RayAdas::ParticleProps m_SmokeParticle, m_EngineParticle;
		RayAdas::ParticleSystem m_ParticleSystem;

		RayAdas::SRef<RayAdas::Texture2D> m_ShipTexture;
		PlayerType character = PlayerType::RUI;
	};

}