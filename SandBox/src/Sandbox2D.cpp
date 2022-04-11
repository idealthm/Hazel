#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

Sanbox2D::Sanbox2D()
	: Layer("Sanbox2D"), m_CameraController(1200.0f / 720.0f)
{
	m_Texture = Hazel::Texture2D::Create("Assets/Textures/back.jpg");
	//m_Texture->Bind();
	//m_Texture->
}

void Sanbox2D::OnAttach()
{
}

void Sanbox2D::OnDetach()
{
}

void Sanbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();
	{
		HZ_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	{
		HZ_PROFILE_SCOPE("RenderCommand::OnUpdate");
		Hazel::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.3f, 1.0f });

		Hazel::RenderCommand::Clear();
	}
	{
		HZ_PROFILE_SCOPE("Renderer2D::BeginScene");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawQuad({ -0.5f, -0.4f }, { 0.8f, 0.3f }, { 0.2f, 0.1f, 0.8f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.3f,  0.3f }, { 0.4f, 0.6f }, { 0.5f, 0.3f, 0.4f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.3f,  0.3f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
		Hazel::Renderer2D::EndScene();
	}
	//m_FlatColorShader->Bind();
	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_color", m_SquareColor);
	//Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, m_FlatColorShader, m_SquareVA, glm::mat4(1.0f));
}

void Sanbox2D::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);

}
