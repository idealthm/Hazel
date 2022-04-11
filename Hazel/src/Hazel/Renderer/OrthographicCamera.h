#pragma once

#include <glm/glm.hpp>
#include "Hazel/Renderer/Camera.h"
namespace Hazel {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float aspectratio, float zoom);
		virtual void SetProjection(float aspectratio, float zoom) override;
		const glm::vec3& GetPosition()const { return m_Position; }
		virtual void SetPosition(const glm::vec3& postion) override { m_Position = postion; RecalculateViewMatrix(); }

		float GetRotation()const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
	protected:
		virtual void RecalculateViewMatrix();
	private:
		float m_Rotation = 0.0f;
	};
}