#include "kat/renderer/Renderer.hpp"
#include <glad/glad.h>
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