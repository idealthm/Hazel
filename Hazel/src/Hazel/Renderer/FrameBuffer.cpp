#include "hzpch.h"
#include "FrameBuffer.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Hazel
{

    Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
    {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "Don't support the RendererAPI!")	return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLFrameBuffer>(spec);
		}
		HZ_CORE_ASSERT(false, "Unknow API!");
		return nullptr;
    }

}