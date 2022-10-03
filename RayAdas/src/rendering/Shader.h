#pragma once

#include <string>
#include <glm/glm.hpp>


// The abstraction of shader.
namespace RayAdas {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetInt(const std::string& name, int value)=0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual const std::string& GetName() const = 0;

		static SRef<Shader> Create(const std::string& filepath);
		static SRef<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const SRef<Shader>& shader);
		void Add(const SRef<Shader>& shader);
		SRef<Shader> Load(const std::string& filepath);
		SRef<Shader> Load(const std::string& name, const std::string& filepath);

		SRef<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, SRef<Shader>> m_Shaders;
	};

}