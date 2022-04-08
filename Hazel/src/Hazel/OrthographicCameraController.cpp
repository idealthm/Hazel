#include "hzpch.h"
#include "OrthographicCameraController.h"

namespace Hazel {
	OrthographicCameraController::OrthographicCameraController(float aspectratio, bool rotation)
		: m_AspectRatio(aspectratio), m_Rotation(rotation), m_Camera(aspectratio, m_ZoomLevel)
	{

	}		

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		float velocity = m_MovementSpeed * ts;

		if (Input::IsKeyPressed(HZ_KEY_W))
			m_CameraPosition.y += velocity;
		if (Input::IsKeyPressed(HZ_KEY_S))
			m_CameraPosition.y -= velocity;
		if (Input::IsKeyPressed(HZ_KEY_A))
			m_CameraPosition.x -= velocity;
		if (Input::IsKeyPressed(HZ_KEY_D))
			m_CameraPosition.x += velocity;
		if (m_Rotation) {
			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_CameraRotation += 90.0f * ts;
			if (Input::IsKeyPressed(HZ_KEY_E))
				m_CameraRotation -= 90.0f * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatch.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
		dispatch.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseMoveEvent));
	}
	void OrthographicCameraController::SetPosition(glm::vec3 position)
	{
		m_CameraPosition = position;
		m_Camera.SetPosition(position);
	}
	void OrthographicCameraController::SetRotation(float rotation)
	{
		if (m_Rotation) {
			m_CameraRotation = rotation;
			m_Camera.SetRotation(m_CameraRotation);
		}
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		if (m_ZoomLevel < 1.0f) m_ZoomLevel = 1.0f;
		if (m_ZoomLevel > 45.0f) m_ZoomLevel = 45.0f;
		m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
		return true;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
		return true;
	}
	bool OrthographicCameraController::OnMouseMoveEvent(MouseMovedEvent& e)
	{
		return false;
	}
}

