#include "FBLevel.h"
#include "Imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Firebird {

	static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
		int H = (int)(hsv.x * 360.0f);
		double S = hsv.y;
		double V = hsv.z;

		double C = S * V;
		double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
		double m = V - C;
		double Rs, Gs, Bs;

		if (H >= 0 && H < 60) {
			Rs = C;
			Gs = X;
			Bs = 0;
		}
		else if (H >= 60 && H < 120) {
			Rs = X;
			Gs = C;
			Bs = 0;
		}
		else if (H >= 120 && H < 180) {
			Rs = 0;
			Gs = C;
			Bs = X;
		}
		else if (H >= 180 && H < 240) {
			Rs = 0;
			Gs = X;
			Bs = C;
		}
		else if (H >= 240 && H < 300) {
			Rs = X;
			Gs = 0;
			Bs = C;
		}
		else {
			Rs = C;
			Gs = 0;
			Bs = X;
		}

		return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
	}


	// Collision detection.
	static bool PointInBarrier(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
	{
		float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
		float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

		if ((s < 0) != (t < 0))
			return false;

		float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

		return A < 0 ?
			(s <= 0 && s + t >= A) :
			(s >= 0 && s + t <= A);
	}

	// Load assets.
	void FBLevel::Init()
	{
		m_TriangleTexture = RayAdas::Texture2D::Create("resources/textures/Triangle.png");
		m_BackgroundTexture = RayAdas::Texture2D::Create("resources/textures/background.jpg");
		m_Player.LoadAssets();

		m_Barriers.resize(5);
		for (int i = 0; i < 5; i++)
			CreateBarrier(i, i * 10.0f);
	}

	void FBLevel::OnUpdate(RayAdas::Timestep ts)
	{
		m_Player.OnUpdate(ts);
		m_Player.LoadAssets();
		if (CollisionTest())
		{
			if (m_Invincible) {
				m_Player.Resurge();
			}
			else {
				GameOver();
			}

			return;
		}

		m_BarrierHSV.x += 0.1f * ts;
		if (m_BarrierHSV.x > 1.0f)
			m_BarrierHSV.x = 0.0f;

		if (m_Player.GetPosition().x > m_BarrierTarget)
		{
			CreateBarrier(m_BarrierIndex, m_BarrierTarget + 20.0f);
			m_BarrierIndex = ++m_BarrierIndex % m_Barriers.size();
			m_BarrierTarget += 10.0f;
		}
	}

	void FBLevel::OnRender()
	{
		const auto& playerPos = m_Player.GetPosition();

		glm::vec4 color = HSVtoRGB(m_BarrierHSV);

		// Background
		RayAdas::RenderUtils::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 35.0f, 35.0f }, 0.0f, m_BackgroundTexture);

		// Floor and ceiling
		RayAdas::RenderUtils::DrawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, color);
		RayAdas::RenderUtils::DrawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);
		
		// Draw barriers.
		for (auto& Barrier : m_Barriers)
		{
			RayAdas::RenderUtils::DrawQuad(Barrier.TopPosition, Barrier.TopScale, glm::radians(180.0f), m_TriangleTexture, color);
			RayAdas::RenderUtils::DrawQuad(Barrier.BottomPosition, Barrier.BottomScale, 0.0f, m_TriangleTexture, color);
		}

		m_Player.OnRender();
	}

	void FBLevel::OnImGuiRender()
	{
		ImGui::Text("Level:");
		ImGui::Checkbox("Switch to invincible model:", &m_Invincible);
		m_Player.OnImGuiRender();
	}

	// create random barrier.
	void FBLevel::CreateBarrier(int index, float offset)
	{
		Barrier& Barrier = m_Barriers[index];
		// xpos.
		Barrier.TopPosition.x = offset;
		Barrier.BottomPosition.x = offset;
		Barrier.TopPosition.z = index * 0.1f - 0.5f;
		Barrier.BottomPosition.z = index * 0.1f - 0.5f + 0.05f;

		float center = Random::Float() * 35.0f - 17.5f;
		float gap = 2.0f + Random::Float() * 5.0f;

		Barrier.TopPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
		Barrier.BottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
	}

	bool FBLevel::CollisionTest()
	{
		if (glm::abs(m_Player.GetPosition().y) > 8.5f)
			return true;

		glm::vec4 playerVertices[4] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};

		const auto& pos = m_Player.GetPosition();
		glm::vec4 playerTransformedVerts[4];
		for (int i = 0; i < 4; i++)
		{
			playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(m_Player.GetRotation()), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f, 1.0f })
				* playerVertices[i];
		}


		// To match Triangle.png (each corner is 10% from the texture edge)
		glm::vec4 BarrierVertices[3] = {
			{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
		};

		for (auto& p : m_Barriers)
		{
			glm::vec2 tri[3];

			// Top Barriers
			for (int i = 0; i < 3; i++)
			{
				tri[i] = glm::translate(glm::mat4(1.0f), { p.TopPosition.x, p.TopPosition.y, 0.0f })
					* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
					* glm::scale(glm::mat4(1.0f), { p.TopScale.x, p.TopScale.y, 1.0f })
					* BarrierVertices[i];
			}

			for (auto& vert : playerTransformedVerts)
			{
				if (PointInBarrier({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
					return true;
			}

			// Bottom Barriers
			for (int i = 0; i < 3; i++)
			{
				tri[i] = glm::translate(glm::mat4(1.0f), { p.BottomPosition.x, p.BottomPosition.y, 0.0f })
					* glm::scale(glm::mat4(1.0f), { p.BottomScale.x, p.BottomScale.y, 1.0f })
					* BarrierVertices[i];
			}

			for (auto& vert : playerTransformedVerts)
			{
				if (PointInBarrier({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
					return true;
			}

		}
		return false;
	}

	void FBLevel::GameOver()
	{
		m_GameOver = true;
	}

	void FBLevel::Reset()
	{
		m_GameOver = false;

		m_Player.Reset();

		m_BarrierTarget = 30.0f;
		m_BarrierIndex = 0;
		for (int i = 0; i < 5; i++)
			CreateBarrier(i, i * 10.0f);
	}
}