#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace Hazel {
	GLenum GetOpenGLType(Hazel::RendererType type)
	{
		switch (type)
		{
		//case Hazel::RendererType::GL_POLYGON: return GL_POLYGON;
			case Hazel::RendererType::TRIANGLES:		return GL_TRIANGLES;
			case Hazel::RendererType::TRIANGLE_STRIP:	return GL_TRIANGLE_STRIP;
			case Hazel::RendererType::LINE_STRIP:		return GL_LINE_STRIP;
		}
		HZ_ASSERT(false,"UnKnow Renderer Type!");
		return GLenum(0);
	}
	void OpenGLRendererAPI::Init()
	{
		HZ_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glLineWidth(1.0);
		//glLineStipple(1, 0x0F0F);
		//gllinest
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GetOpenGLType(type), vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}