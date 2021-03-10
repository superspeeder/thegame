#include "kat/renderer/Buffer.hpp"

#include <spdlog/spdlog.h>

kat::VertexBuffer::VertexBuffer(std::vector<float> data, BufferMode mode) : m_Data(data), m_Mode(mode), m_EffectiveSize(data.size()) {
	glGenBuffers(1, &m_Buffer);
	push();
	spdlog::debug("Created VertexBuffer({0}, {2}) : {1} bytes", m_Buffer, data.size() * sizeof(float), mode);
}

kat::VertexBuffer::VertexBuffer(uint32_t size, BufferMode mode) : m_Data(size), m_Mode(mode) {
	glGenBuffers(1, &m_Buffer);
	push();
	spdlog::debug("Created VertexBuffer({0}, {2}) : {1} bytes", m_Buffer, size * sizeof(float), mode);
}

kat::VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_Buffer);
	spdlog::debug("Deleted VertexBuffer({0})", m_Buffer);
}


void kat::VertexBuffer::set(std::vector<float> data) {
	if (data.size() > m_Data.size()) {
		m_SizeDirty = true;
	}
	m_Data = data;
	update();
}

void kat::VertexBuffer::push() {
	bind();
	glBufferData(GL_ARRAY_BUFFER, m_Data.size() * sizeof(float), m_Data.data(), static_cast<GLenum>(m_Mode));
	unbind();
	m_SizeDirty = false;
}

void kat::VertexBuffer::update() {
	if (m_SizeDirty) {
		push();
	}
	else {
		bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_EffectiveSize * sizeof(float), m_Data.data());
		unbind();
	}
}

void kat::VertexBuffer::update(std::vector<float> data, uint32_t offset) {
	uint32_t endp = data.size() + offset;
	if (endp > m_Data.size()) {
		spdlog::error("Error updating VertexBuffer({0}) with given data. Data is too large. Updating with largest possible dataset", m_Buffer);
		endp = m_Data.size();
	}

	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), (endp - offset) * sizeof(float), data.data());
	unbind();
}

void kat::VertexBuffer::forceResize(uint32_t newSize) {
	if (newSize == m_Data.size()) return;
	m_Data.resize(newSize);
	m_SizeDirty = true;
}


void kat::VertexBuffer::setVal(uint32_t index, float v) {
	if (index >= m_Data.size()) {
		spdlog::error("VertexBuffer({0}) doesn't contain index {1}", m_Buffer, index);
	}
	if (index > m_EffectiveSize) {
		m_EffectiveSize = index + 1;
	}
	m_Data[index] = v;
}

void kat::VertexBuffer::pushVal(float v) {
	if (m_EffectiveSize < m_Data.size()) {
		m_Data[m_EffectiveSize++] = v;
	}
	else {
		m_Data.push_back(v);
		m_EffectiveSize++;
	}
}

void kat::VertexBuffer::reset() {
	m_EffectiveSize = 0;
}

void kat::VertexBuffer::shrink(uint32_t size) {
	m_EffectiveSize = size;
}

void kat::VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
}

void kat::VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t kat::VertexBuffer::getName() {
	return m_Buffer;
}

uint32_t kat::VertexBuffer::getEffectiveSize() {
	return m_EffectiveSize;
}


kat::ElementBuffer::ElementBuffer(std::vector<uint32_t> data, BufferMode mode) : m_Data(data), m_Mode(mode), m_EffectiveSize(data.size()) {
	glGenBuffers(1, &m_Buffer);
	push();
	spdlog::debug("Created ElementBuffer({0}, {2}) : {1} bytes", m_Buffer, data.size() * sizeof(uint32_t), mode);
}

kat::ElementBuffer::ElementBuffer(uint32_t size, BufferMode mode) : m_Data(size), m_Mode(mode) {
	glGenBuffers(1, &m_Buffer);
	push();
	spdlog::debug("Created ElementBuffer({0}, {2}) : {1} bytes", m_Buffer, size * sizeof(uint32_t), mode);
}

kat::ElementBuffer::~ElementBuffer() {
	glDeleteBuffers(1, &m_Buffer);
	spdlog::debug("Deleted ElementBuffer({0})", m_Buffer);
}


void kat::ElementBuffer::set(std::vector<uint32_t> data) {
	if (data.size() > m_Data.size()) {
		m_SizeDirty = true;
	}
	m_Data = data;
	update();
}

void kat::ElementBuffer::push() {
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Data.size() * sizeof(uint32_t), m_Data.data(), static_cast<GLenum>(m_Mode));
	unbind();
	m_SizeDirty = false;
}

void kat::ElementBuffer::update() {
	if (m_SizeDirty) {
		push();
	}
	else {
		bind();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_EffectiveSize * sizeof(uint32_t), m_Data.data());
		unbind();
	}
}

void kat::ElementBuffer::update(std::vector<uint32_t> data, uint32_t offset) {
	uint32_t endp = data.size() + offset;
	if (endp > m_Data.size()) {
		spdlog::error("Error updating ElementBuffer({0}) with given data. Data is too large. Updating with largest possible dataset", m_Buffer);
		endp = m_Data.size();
	}

	bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), (endp - offset) * sizeof(uint32_t), data.data());
	unbind();
}

void kat::ElementBuffer::forceResize(uint32_t newSize) {
	if (newSize == m_Data.size()) return;
	m_Data.resize(newSize);
	m_SizeDirty = true;
}


void kat::ElementBuffer::setVal(uint32_t index, uint32_t v) {
	if (index >= m_Data.size()) {
		spdlog::error("ElementBuffer({0}) doesn't contain index {1}", m_Buffer, index);
	}
	if (index > m_EffectiveSize) {
		m_EffectiveSize = index + 1;
	}
	m_Data[index] = v;
}

void kat::ElementBuffer::pushVal(uint32_t v) {
	if (m_EffectiveSize < m_Data.size()) {
		m_Data[m_EffectiveSize++] = v;
	}
	else {
		m_Data.push_back(v);
		m_EffectiveSize++;
	}
}

void kat::ElementBuffer::reset() {
	m_EffectiveSize = 0;
}

void kat::ElementBuffer::shrink(uint32_t size) {
	m_EffectiveSize = size;
}

void kat::ElementBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer);
}

void kat::ElementBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t kat::ElementBuffer::getName() {
	return m_Buffer;
}

uint32_t kat::ElementBuffer::getEffectiveSize() {
	return m_EffectiveSize;
}

