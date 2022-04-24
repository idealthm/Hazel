#include "hzpch.h"

#include "PerspectiveCameraController.h"


namespace Hazel
{
    PerspectiveCameraController::PerspectiveCameraController(float aspectratio)
        : m_AspectRatio(aspectratio), m_Camera(aspectratio, m_ZoomLevel)
    {
    }
    void PerspectiveCameraController::OnUpdate(Timestep ts)
    {
        HZ_PROFILE_FUNCTION();

        float velocity = m_MovementSpeed * ts;

        if (Input::IsKeyPressed(HZ_KEY_W))
            m_CameraPosition += m_Camera.GetFront() * velocity;
        if (Input::IsKeyPressed(HZ_KEY_S))
            m_CameraPosition -= m_Camera.GetFront() * velocity;
        if (Input::IsKeyPressed(HZ_KEY_A))
            m_CameraPosition -= m_Camera.GetRight() * velocity;
        if (Input::IsKeyPressed(HZ_KEY_D))
            m_CameraPosition += m_Camera.GetRight() * velocity;
        if (Input::IsKeyPressed(HZ_KEY_LEFT_SHIFT))
            m_CameraPosition += m_Camera.GetUp() * velocity;
        if (Input::IsKeyPressed(HZ_KEY_SPACE))
            m_CameraPosition -= m_Camera.GetUp() * velocity;
        
        m_Camera.SetPosition(m_CameraPosition);
    }
    void PerspectiveCameraController::OnEvent(Event& e)
    {
        HZ_PROFILE_FUNCTION();

        EventDispatcher dispatch(e);
        dispatch.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
        dispatch.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
        dispatch.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoveEvent));
    }

    void PerspectiveCameraController::SetPosition(glm::vec3 position) 
    {
        HZ_PROFILE_FUNCTION();

        m_CameraPosition = position;
        m_Camera.SetPosition(position);
    }

    bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        HZ_PROFILE_FUNCTION();

        m_ZoomLevel -= e.GetYOffset();
        if (m_ZoomLevel < 1.0f) m_ZoomLevel = 1.0f;
        if (m_ZoomLevel > 45.0f) m_ZoomLevel = 45.0f;
        m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
        return true;
    }
    bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        HZ_PROFILE_FUNCTION();

        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
        return true;
    }

    bool PerspectiveCameraController::OnMouseMoveEvent(MouseMovedEvent& e)
    {
        HZ_PROFILE_FUNCTION();

        static float posx = (float)e.GetX(), posy = (float)e.GetY();
        float yaw = m_Camera.GetYaw() + (e.GetX() - posx) * m_MouseSensitivity;
        float pitch = m_Camera.GetPitch() - (e.GetY() - posy) * m_MouseSensitivity;
        m_Camera.SetYaw(yaw);
        m_Camera.SetPitch(pitch);
        posx = e.GetX();
        posy = e.GetY();
        return true;
    }
}