#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class Camera
	{
	public:
		Camera() = default;

		virtual void SetProjection(float aspectratio, float zoom) = 0;
		virtual void SetPosition(const glm::vec3& postion) = 0;
		const glm::vec3& GetPosition()const { return m_Position; }

		const glm::mat4 GetProjectionMatrix()const { return m_ProjectionMatrix; }
		const glm::mat4 GetViewMatrix()const { return m_ViewMatrix; }
		const glm::mat4 GetViewProjectionMatrix()const { return m_ViewProjectionMatrix; }
	protected:
		virtual void RecalculateViewMatrix() = 0;
	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
	};
}