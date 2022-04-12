#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(size);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false,"Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices,size);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t Count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, Count);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		return nullptr;
	}
}