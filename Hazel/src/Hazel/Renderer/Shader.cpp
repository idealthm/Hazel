#include <hzpch.h>
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(path);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		
		return nullptr;
	}
	void ShaderLibrary::Add(const Ref<Shader> shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader> shader)
	{
		HZ_CORE_ASSERT(!Exists(name), "Shader already exist!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto& shader = Shader::Create(path);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto& shader = Shader::Create(path);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		HZ_CORE_ASSERT(Exists(name), "Shader Not Exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}