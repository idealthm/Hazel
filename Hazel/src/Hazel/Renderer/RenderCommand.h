#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand {
	public:
		static void Init() { s_RendererAPI->Init(); }
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
		static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static void SetCursorDisabled(bool enabled) { s_RendererAPI->SetCursorDisabled(enabled); }

		static void Clear() { s_RendererAPI->Clear(); }
		inline static void DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray, uint32_t indexcount=0)
		{
			s_RendererAPI->DrawIndexed(type, vertexArray, indexcount);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}