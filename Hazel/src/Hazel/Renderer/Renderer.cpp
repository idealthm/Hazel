#include "hzpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"


namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
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

		vertexArray->Bind();
		RenderCommand::DrawIndexed(type, vertexArray);
	}

}