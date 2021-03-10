#pragma once

#include <glad/glad.h>
#include "kat/renderer/Buffer.hpp"

namespace kat {


	class VertexArray {
	private:
		uint32_t m_VertexArray;
		uint32_t m_NextIndex = 0;
	public:
		
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

		void attachEBO(kat::ElementBuffer* ebo);

		void attribute(uint32_t size, uint32_t stride, uint32_t offset);

		void vbo(kat::VertexBuffer* vbo, std::vector<uint32_t> defs);
	};
}