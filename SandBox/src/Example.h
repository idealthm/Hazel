#pragma once

#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer();
	void OnUpdate(Hazel::Timestep ts) override;
	void OnEvent(Hazel::Event& e) override;
	void OnImGuiRender() override;

private:
	Hazel::ShaderLibrary m_Shaders;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray, m_TVArray;
	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;
	Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_LogoTexture;

	Hazel::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
};