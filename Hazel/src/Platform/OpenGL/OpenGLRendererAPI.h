#pragma once

#include <Hazel/Renderer/RendererAPI.h>

namespace Hazel {

	class OpenGLRendererAPI : public RendererAPI {

		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		// Í¨¹ý RendererAPI ¼Ì³Ð
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetCursorDisabled(bool enabled) override;
		virtual void Clear() override;
		virtual void DrawIndexed(RendererType type,const Ref<VertexArray>& vertexArray, uint32_t indexcount = 0) override;

	};

}