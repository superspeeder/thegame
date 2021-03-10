#include "camera.hpp"

Camera::Camera(float left, float bottom, float right, float top) {
	proj = glm::ortho(left, right, bottom, top);
	view = glm::mat4(1.0f);
	pos = { 0, 0 };
}

void Camera::update() {
	if (isDirty) {
		view = glm::translate(glm::mat4(1.0f), glm::vec3(-pos, 0.0f));
		isDirty = false;
	}
}

void Camera::translate(float dx, float dy) {
	pos += glm::vec2{ dx, dy };
	isDirty = true;
}

void Camera::setPos(float x, float y) {
	pos = { x, y };
	isDirty = true;
}

glm::mat4 Camera::getProj() {
	return proj;
}

glm::mat4 Camera::getView() {
	return view;
}

glm::mat4 Camera::getCombined() {
	return proj * view;
}
