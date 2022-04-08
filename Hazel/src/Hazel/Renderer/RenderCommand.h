#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand {
	public:
		static void Init() { s_RendererAPI->Init(); }
		static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static void Clear() { s_RendererAPI->Clear(); }
		inline static void DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(type, vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}