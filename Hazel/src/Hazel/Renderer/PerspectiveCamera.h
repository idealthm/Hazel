#pragma once

#include <vector>
#include "Hazel/Core/Timestep.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Hazel/Camera.h"
typedef unsigned char GLboolean;
namespace Hazel {
    class PerspectiveCamera : public Camera{
    public:
        PerspectiveCamera(float aspectratio, float zoom);
        virtual void SetProjection(float aspectratio, float zoom) override;

        const glm::vec3& GetPosition()const { return m_Position; }
        virtual void SetPosition(const glm::vec3& postion) override;

        glm::vec3 GetFront() { return m_Front; }
        glm::vec3 GetRight() { return m_Right; }
        glm::vec3 GetUp() { return glm::cross(m_Front, m_Right); }
        

        float GetYaw() { return m_Yaw; }
        void SetYaw(float yaw) { m_Yaw = yaw; RecalculateViewMatrix(); }
        float GetPitch() { return m_Pitch; }
        void SetPitch(float pitch) { m_Pitch = pitch; RecalculateViewMatrix(); }
        void SetEulerAngles(float yaw, float pitch) { m_Yaw = yaw; m_Pitch = pitch; RecalculateViewMatrix(); }
    private:
        // 重新计算视角矩阵｛将相机位置调整到原点｝
        void RecalculateViewMatrix();
    private:
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;
        // euler Angles
        float m_Yaw;
        float m_Pitch;  
    };
}