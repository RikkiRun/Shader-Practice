#pragma once
#include <glm\glm.hpp>

class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;

public:
	Camera();
	~Camera();
	glm::mat4 getWorldToViewMatrix() const;
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
	void mouseUpdate(const glm::vec2& newMousePosition);
};