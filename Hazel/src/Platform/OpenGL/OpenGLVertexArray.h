#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {

	class OpenGLVertexArray :public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray();
		OpenGLVertexArray();
		// Í¨¹ý VertexArray ¼Ì³Ð
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const { return m_VertexBuffer; }
		const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}