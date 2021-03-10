#include "kat/renderer/VertexArray.hpp"
#include <spdlog/spdlog.h>


kat::VertexArray::VertexArray() {
	glCreateVertexArrays(1, &m_VertexArray);
	spdlog::debug("Created VertexArray({0})", m_VertexArray);
}

kat::VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_VertexArray);
	spdlog::debug("Deleted VertexArray({0})", m_VertexArray);
}

void kat::VertexArray::bind() {
	glBindVertexArray(m_VertexArray);
}

void kat::VertexArray::unbind() {
	glBindVertexArray(0);
}

void kat::VertexArray::attribute(uint32_t size, uint32_t stride, uint32_t offset) {
	bind();
	glVertexAttribPointer(m_NextIndex, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (const void*)(offset * sizeof(float)));
	glEnableVertexArrayAttrib(m_VertexArray, m_NextIndex);
	spdlog::debug("Added Attribute ({1}, {2} floats, {3} floats offset, {4} float stride) to VertexArray({0})", m_VertexArray, m_NextIndex, size, offset, stride);
	unbind();
	m_NextIndex++;
}

struct def {
	uint32_t size, offset;
};

void kat::VertexArray::vbo(kat::VertexBuffer* vbo, std::vector<uint32_t> defs) {
	std::vector<def> defs_;
	uint32_t stride = 0;
	
	for (uint32_t s : defs) {
		defs_.push_back({ s, stride });
		stride += s;
	}

	vbo->bind();
	for (const def& d : defs_) {
		attribute(d.size, stride, d.offset);
	}
	vbo->unbind();
}

void kat::VertexArray::attachEBO(kat::ElementBuffer* ebo) {
	bind();
	glVertexArrayElementBuffer(m_VertexArray, ebo->getName());
	unbind();
}


