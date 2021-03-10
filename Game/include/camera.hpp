#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
private:
	glm::mat4 proj;
	glm::mat4 view;

	glm::vec2 pos;

	bool isDirty = true;
public:
	
	Camera(float left, float bottom, float right, float top);

	void update();
	void translate(float dx, float dy);
	void setPos(float x, float y);

	inline glm::vec2 getPos() { return pos; };

	glm::mat4 getProj();
	glm::mat4 getView();
	glm::mat4 getCombined();
};
