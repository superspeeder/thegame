#include "kat/renderer/Renderer.hpp"
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

bool kat::isGLADInit = false;

void kat::initGLAD() {
	if (!kat::isGLADInit) {
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		kat::isGLADInit = true;
		spdlog::info("Initialized GLAD");
	}
}

void kat::clearFrame(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void kat::drawArrays(kat::DrawMode mode, kat::VertexArray* vao, uint32_t count, uint32_t first) {
	vao->bind();
	glDrawArrays(static_cast<GLenum>(mode), count, first);
	vao->unbind();
}

void kat::drawElements(kat::DrawMode mode, kat::VertexArray* vao, uint32_t count, uint32_t first) {
	vao->bind();
	glDrawElements(static_cast<GLenum>(mode), count, GL_UNSIGNED_INT, (const void*)first);
	vao->unbind();
}

void kat::enableBlend() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

