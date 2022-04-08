#pragma once

#include <Hazel/Renderer/RendererAPI.h>

namespace Hazel {

	class OpenGLRendererAPI : public RendererAPI {

		virtual void Init() override;
		// Í¨¹ý RendererAPI ¼Ì³Ð
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray) override;
	};

}