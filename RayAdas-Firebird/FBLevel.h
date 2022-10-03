#pragma once

#include "FBPlayer.h"

namespace Firebird {

	struct Barrier
	{
		glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
		glm::vec2 TopScale = { 15.0f, 20.0f };

		glm::vec3 BottomPosition = { 10.0f, 10.0f, 0.0f };
		glm::vec2 BottomScale = { 15.0f, 20.0f };
	};

	class FBLevel
	{
	public:
		void Init();

		void OnUpdate(RayAdas::Timestep ts);
		void OnRender();

		void OnImGuiRender();

		bool IsGameOver() const { return m_GameOver; }
		void Reset();

		FBPlayer& GetPlayer() { return m_Player; }
	private:
		void CreateBarrier(int index, float offset);
		bool CollisionTest();

		void GameOver();
	private:
		FBPlayer m_Player;

		bool m_GameOver = false;

		float m_BarrierTarget = 30.0f;
		int m_BarrierIndex = 0;
		bool m_Invincible = false;
		glm::vec3 m_BarrierHSV = { 0.0f, 0.8f, 0.8f };

		std::vector<Barrier> m_Barriers;

		RayAdas::SRef<RayAdas::Texture2D> m_TriangleTexture;
		RayAdas::SRef<RayAdas::Texture2D> m_BackgroundTexture;
	};
}