#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

Sanbox2D::Sanbox2D()
	: Layer("Sanbox2D"), m_CameraController(1200.0f / 720.0f)
{
}

void Sanbox2D::OnAttach()
{
}

void Sanbox2D::OnDetach()
{
}

void Sanbox2D::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.3f, 1.0f });

	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawQuad({ -0.5f, -0.4f }, { 0.8f,0.3f }, { 0.2f, 0.1f, 0.8f, 1.0f });
	Hazel::Renderer2D::DrawQuad({  0.3f,  0.3f }, { 0.4f,0.6f }, { 0.5f, 0.3f, 0.4f, 1.0f });
	Hazel::Renderer2D::EndScene();

	//m_FlatColorShader->Bind();
	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_color", m_SquareColor);
	//Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, m_FlatColorShader, m_SquareVA, glm::mat4(1.0f));
}

void Sanbox2D::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);

}
