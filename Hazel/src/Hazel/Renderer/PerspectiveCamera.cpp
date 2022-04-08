#include <hzpch.h>

#include "PerspectiveCamera.h"

#include <glad/glad.h>
namespace Hazel{


    PerspectiveCamera::PerspectiveCamera(float aspectratio, float zoom)
        : m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        m_Yaw = -90.0f;
        m_Pitch = 0.0f;
        m_ProjectionMatrix = glm::perspective(glm::radians(zoom), aspectratio, 0.1f, 100.0f);
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::SetProjection(float aspectratio, float zoom)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(zoom), aspectratio, 0.1f, 100.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& postion)
    {
        m_Position = postion;
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        //m_ProjectionMatrix = glm::perspective(glm::radians(m_Zoom), m_AspectRatio, 0.1f, 100.0f);
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

};


