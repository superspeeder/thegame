#pragma once

#include <glad/glad.h>
#include <vector>
#include <memory>

namespace kat {

	enum class BufferMode {
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY
	};


	/**
	 * Its smart. uses effective size to minimize the number of reallocations done on the gpu (use StreamVertexBuffer for stream buffers since it is optimized for streaming). For advanced meshes, use the OptimizedMesh class (it wont duplicate vertices). 
	 */
	class VertexBuffer {
	private:
		std::vector<float> m_Data;
		uint32_t m_EffectiveSize = 0;
		BufferMode m_Mode;
		uint32_t m_Buffer;
		bool m_SizeDirty = true;

	public:
		VertexBuffer(std::vector<float> data, BufferMode mode = BufferMode::StaticDraw);
		VertexBuffer(uint32_t size, BufferMode mode = BufferMode::StaticDraw);

		~VertexBuffer();

		void forceResize(uint32_t newSize); // Force the internal buffer to resize instead of just changing effective size

		void set(std::vector<float> data);
		void push();
		void update();
		void update(std::vector<float> data, uint32_t offset = 0);
		
		void setVal(uint32_t index, float v);
		void pushVal(float v);

		void reset();
		void shrink(uint32_t size);

		void bind();
		void unbind();

		uint32_t getName();

		uint32_t getEffectiveSize();
		
	};


	class ElementBuffer {
	private:
		std::vector<uint32_t> m_Data;
		uint32_t m_EffectiveSize = 0;
		BufferMode m_Mode;
		uint32_t m_Buffer;
		bool m_SizeDirty = true;

	public:
		ElementBuffer(std::vector<uint32_t> data, BufferMode mode = BufferMode::StaticDraw);
		ElementBuffer(uint32_t size, BufferMode mode = BufferMode::StaticDraw);

		~ElementBuffer();

		void forceResize(uint32_t newSize); // Force the internal buffer to resize instead of just changing effective size

		void set(std::vector<uint32_t> data);
		void push();
		void update();
		void update(std::vector<uint32_t> data, uint32_t offset = 0);

		void setVal(uint32_t index, uint32_t v);
		void pushVal(uint32_t v);

		void reset();
		void shrink(uint32_t size);

		void bind();
		void unbind();

		uint32_t getName();

		uint32_t getEffectiveSize();
	};
}