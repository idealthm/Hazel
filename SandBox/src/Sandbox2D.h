#pragma once

#include <Hazel.h>
class Sanbox2D : public Hazel::Layer
{
public:					
	Sanbox2D();
	virtual ~Sanbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Hazel::Timestep ts) override;	
	void OnEvent(Hazel::Event& event) override;

	void OnImGuiRender() override;
private:
	Hazel::OrthographicCameraController m_CameraController;

	// Temp
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	Hazel::Ref<Hazel::Texture2D> m_Texture;
	Hazel::Ref<Hazel::FrameBuffer> m_FrameBuffer;

	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};