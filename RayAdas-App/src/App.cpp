﻿#include <RayAdas.h>

#include "platform/opengl/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public RayAdas::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(RayAdas::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		RayAdas::SRef<RayAdas::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(RayAdas::VertexBuffer::Create(vertices, sizeof(vertices)));
		RayAdas::BufferLayout layout = {
			{ RayAdas::ShaderDataType::Float3, "a_Position" },
			{ RayAdas::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		RayAdas::SRef<RayAdas::IndexBuffer> indexBuffer;
		indexBuffer.reset(RayAdas::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(RayAdas::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		RayAdas::SRef<RayAdas::VertexBuffer> squareVB;
		squareVB.reset(RayAdas::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ RayAdas::ShaderDataType::Float3, "a_Position" },
			{ RayAdas::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		RayAdas::SRef<RayAdas::IndexBuffer> squareIB;
		squareIB.reset(RayAdas::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = RayAdas::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = RayAdas::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("resources/shaders/Texture.glsl");

		m_Texture = RayAdas::Texture2D::Create("resources/textures/haruluya.jpg");
		m_ChernoLogoTexture = RayAdas::Texture2D::Create("resources/textures/haruluya.jpg");

		std::dynamic_pointer_cast<RayAdas::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<RayAdas::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(RayAdas::Timestep ts) override
	{
		if (RayAdas::Input::IsKeyPressed(RA_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (RayAdas::Input::IsKeyPressed(RA_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (RayAdas::Input::IsKeyPressed(RA_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (RayAdas::Input::IsKeyPressed(RA_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (RayAdas::Input::IsKeyPressed(RA_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (RayAdas::Input::IsKeyPressed(RA_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		RayAdas::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RayAdas::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		RayAdas::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<RayAdas::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<RayAdas::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				RayAdas::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		RayAdas::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		RayAdas::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// RayAdas::Renderer::Submit(m_Shader, m_VertexArray);

		RayAdas::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(RayAdas::Event& event) override
	{
	}
private:
	RayAdas::ShaderLibrary m_ShaderLibrary;
	RayAdas::SRef<RayAdas::Shader> m_Shader;
	RayAdas::SRef<RayAdas::VertexArray> m_VertexArray;

	RayAdas::SRef<RayAdas::Shader> m_FlatColorShader;
	RayAdas::SRef<RayAdas::VertexArray> m_SquareVA;

	RayAdas::SRef<RayAdas::Texture2D> m_Texture, m_ChernoLogoTexture;

	RayAdas::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public RayAdas::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

RayAdas::Application* RayAdas::CreateApplication()
{
	return new Sandbox();
}