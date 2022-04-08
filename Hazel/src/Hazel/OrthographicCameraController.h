#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Renderer/PerspectiveCamera.h"
#include "Hazel/core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Input.h"
#include "KeyCodes.h"

#include "Camera.h"

namespace Hazel {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectratio, bool rotation);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetPosition(glm::vec3 position);
		void SetRotation(float rotation);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseMoveEvent(MouseMovedEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 45.0f;
		float m_MovementSpeed = 1.5f;
		float m_CameraRotation = 0.0f;
		float m_MouseSensitivity = 0.1f;
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,3.0f };
		OrthographicCamera m_Camera;


		bool m_Rotation;
	};
}