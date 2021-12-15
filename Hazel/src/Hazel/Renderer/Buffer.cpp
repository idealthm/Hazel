#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HZ_CORE_ASSERT(false,"Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices,size);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t Count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HZ_CORE_ASSERT(false, "Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, Count);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		return nullptr;
	}
}