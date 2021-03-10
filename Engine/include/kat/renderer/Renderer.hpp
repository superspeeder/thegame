#pragma once
#include <glad/glad.h>
#include "kat/renderer/VertexArray.hpp"

namespace kat {

	enum class DrawMode {
		Triangles = GL_TRIANGLES
	};

	extern bool isGLADInit;

	void initGLAD();

	void enableBlend();

	void clearFrame(float r, float g, float b, float a = 1.0f);

	void drawArrays(DrawMode mode, kat::VertexArray* vao, uint32_t count, uint32_t first = 0);
	void drawElements(DrawMode mode, kat::VertexArray* vao, uint32_t count, uint32_t first = 0);
}