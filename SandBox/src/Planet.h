#pragma once

#include <Hazel.h>
#include <vector>

class PlanetLayer : public Hazel::Layer
{
public:
	PlanetLayer();
	void OnUpdate(Hazel::Timestep ts) override;
	void OnEvent(Hazel::Event& e) override;
	void OnImGuiRender();

	enum class CameraControl{
		None,
		Sun,
		Earth,
		Moon
	};

private:
	static std::vector<float> GetCircleVertex(float radius, uint32_t slices = 6);

	static std::vector<float> GetSphereVertex(float radius, uint32_t slices = 6, uint32_t stacks = 6);

	static std::vector<uint32_t> GetCircleIndex(uint32_t slices = 6);

	static std::vector<uint32_t> GetSphereIndex(uint32_t slices = 6, uint32_t stacks = 6);

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& e);
private:
	// ShaderLibaray
	Hazel::ShaderLibrary m_Shaders;
	// VertexBuffer
	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;
	// VertexArray
	Hazel::Ref<Hazel::VertexArray> m_VertexArray, m_BoxArray, m_CAO;
	// IndexArray
	Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;
	// Camera
	Hazel::PerspectiveCameraController m_CameraController; 
	// Texture
	Hazel::Ref<Hazel::Texture> m_Texture;

	glm::vec3 m_EarthPosition, m_MoonPosition, m_SunPosition, m_SpacecraftPosition;
	
	float m_SunToEarthLength = 1.0f;
	float m_EarthToMoonLength = 0.3f;

	float m_RotateSpeed = 1.0f;

	float m_MoonRotation = 0.0f;
	float m_EarthRotation = 0.0f;
	float m_SpacecraftRotation = 0.0f;

	static CameraControl m_Control;
	static CameraControl m_ViewControl;
};