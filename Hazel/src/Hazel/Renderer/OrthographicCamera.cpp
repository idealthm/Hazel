#include "hzpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel{

	OrthographicCamera::OrthographicCamera(float aspectratio, float zoom)
		// 设置屏幕横纵比
		// near : -1.0f
		// far : 1.0f
	{
		m_ProjectionMatrix = glm::ortho(-aspectratio * zoom, aspectratio * zoom, -zoom, zoom, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		// translate : 将坐标转化成矩阵
		// rotate : 将角度转化成矩阵
		// 先位移再旋转
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		// 上面是从原点到相机位置的转换矩阵
		// 求逆之后就是讲相机位置调整到原点的矩阵
		m_ViewMatrix = glm::inverse(transform);

		// 因为OpenGL是列向量（右乘），因此是先进行视角变换再进行投影变换
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetProjection(float aspectratio, float zoom)
	{
		m_ProjectionMatrix = glm::ortho(-aspectratio * zoom, aspectratio * zoom, -zoom, zoom, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
