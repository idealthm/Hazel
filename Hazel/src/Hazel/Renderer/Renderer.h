#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "PerspectiveCamera.h"
#include <glm/glm.hpp>
namespace Hazel
{
	class Renderer {
	public:
		static void Init() ;
		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const Camera& camera);
		static void BeginScene(const Ref<Camera> camera);
		static void EndScene();
		static void Submit(RendererType type,const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData 
		{
			glm::mat4 Projection;
			glm::mat4 View;
		};
		static SceneData* m_SceneData;
	};
}