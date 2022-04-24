#pragma once 

#include "Hazel/Renderer/FrameBuffer.h"

namespace Hazel
{

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);

		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; };
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; };
	private:

		uint32_t m_RendererID, m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	};
}