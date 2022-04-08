#include "hzpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel{

	OrthographicCamera::OrthographicCamera(float aspectratio, float zoom)
		// ������Ļ���ݱ�
		// near : -1.0f
		// far : 1.0f
	{
		m_ProjectionMatrix = glm::ortho(-aspectratio * zoom, aspectratio * zoom, -zoom, zoom, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		// translate : ������ת���ɾ���
		// rotate : ���Ƕ�ת���ɾ���
		// ��λ������ת
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		// �����Ǵ�ԭ�㵽���λ�õ�ת������
		// ����֮����ǽ����λ�õ�����ԭ��ľ���
		m_ViewMatrix = glm::inverse(transform);

		// ��ΪOpenGL�����������ҳˣ���������Ƚ����ӽǱ任�ٽ���ͶӰ�任
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetProjection(float aspectratio, float zoom)
	{
		m_ProjectionMatrix = glm::ortho(-aspectratio * zoom, aspectratio * zoom, -zoom, zoom, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
