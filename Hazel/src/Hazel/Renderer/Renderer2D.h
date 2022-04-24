#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Hazel {

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);

		// Stats
		struct Statistic
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GettotalVertexCount() { return QuadCount * 4; }
			uint32_t GettotalIndexCount() { return QuadCount * 6; }
		};

		static Statistic GetStats();
		static void ResetStats();
	private:
		static void FlushAndReset();
	};
}