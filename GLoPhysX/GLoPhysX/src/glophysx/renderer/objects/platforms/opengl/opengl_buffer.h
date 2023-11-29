#pragma once
/**
 * @file opengl_buffer.h
 * @brief Declaration of OpenglVertexBuffer and OpenglIndexBuffer classes.
 *
 * This header file defines the OpenglVertexBuffer and OpenglIndexBuffer classes, which represent the
 * OpenGL implementations for handling vertex and index buffers in the GLoPhysX renderer. These classes
 * extend the VertexBuffer and IndexBuffer base classes, providing platform-specific functionality for
 * OpenGL graphics rendering.
 *
 * @see VertexBuffer, IndexBuffer
 * @version 1.0
 * @date 2023-10-27
 * @author Secareanu Filip
 */

#include "glophysx/renderer/objects/buffer/buffer.h"
#include "glophysx/renderer/objects/buffer/buffer_layout.h"

namespace GLOPHYSX {

	namespace RENDERER {

		class OpenglVertexBuffer: public VertexBuffer
		{
		public:
			OpenglVertexBuffer(float* vertices, uint32_t size);
			virtual ~OpenglVertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
			virtual const BufferLayout& GetLayout() const override { return m_layout; }

		private:
			uint32_t m_buffer_id;

			BufferLayout m_layout;
		};

		class OpenglIndexBuffer : public IndexBuffer
		{
		public:
			OpenglIndexBuffer(uint32_t* indices, uint32_t count);
			virtual ~OpenglIndexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual uint32_t GetCount() const override { return m_count; }

		private:
			uint32_t m_buffer_id;
			uint32_t m_count;
		};
	}
}
