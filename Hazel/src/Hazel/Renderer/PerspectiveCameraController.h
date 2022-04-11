#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/PerspectiveCamera.h"
#include "Hazel/core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"

#include "Camera.h"

namespace Hazel {

	class PerspectiveCameraController {
	public:
		PerspectiveCameraController(float aspectratio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		void SetPosition(glm::vec3 position);
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
		PerspectiveCamera m_Camera;
	};
}