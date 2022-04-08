#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Hazel {

	enum class RendererType
	{
		POLYGON,
		TRIANGLES,
		TRIANGLE_STRIP,
		LINE_STRIP,
		
	};

	class RendererAPI 
	{
	public:
		enum class API 
		{
			None, OpenGL = 1
		};
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;

	};
}
