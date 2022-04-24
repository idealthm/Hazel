#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		HZ_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::SetCursorDisabled(bool enabled)
	{
		RenderCommand::SetCursorDisabled(enabled);
	}

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_SceneData->Projection = camera.GetProjectionMatrix();
		m_SceneData->View = camera.GetViewMatrix();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		m_SceneData->Projection =  camera.GetProjectionMatrix();
		m_SceneData->View = camera.GetViewMatrix();
	}

	void Renderer::BeginScene(const Ref<Camera> camera)
	{
		m_SceneData->Projection = camera->GetProjectionMatrix();
		m_SceneData->View = camera->GetViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(RendererType type, const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Projection", m_SceneData->Projection);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_View", m_SceneData->View);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", transform);

		RenderCommand::DrawIndexed(type, vertexArray);
	}

}