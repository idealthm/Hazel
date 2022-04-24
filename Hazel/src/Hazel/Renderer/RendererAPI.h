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
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetCursorDisabled(bool enabled) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray, uint32_t indexcount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;

	};
}
