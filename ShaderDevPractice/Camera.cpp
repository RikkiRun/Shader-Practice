#include "Camera.h"
#include <glm\gtx\transform.hpp>



Camera::Camera() :
	viewDirection(-0.06f, -0.43f, -0.77f),
	position(0.50f, 3.63f, 4.53f),
	UP(0.0f, 1.0f, 0.0f)
{
}

const float MOVEMENT_SPEED = 0.1f;

void Camera::moveForward()
{
	position += MOVEMENT_SPEED * viewDirection;
}

void Camera::moveBackward()
{
	position += -MOVEMENT_SPEED * viewDirection;

}

void Camera::strafeLeft()
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += -MOVEMENT_SPEED * strafeDirection;
}

void Camera::strafeRight()
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += MOVEMENT_SPEED * strafeDirection;
}

void Camera::moveUp()
{
	position += MOVEMENT_SPEED * UP;
}

void Camera::moveDown()
{
	position += -MOVEMENT_SPEED * UP;
}


void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 10.0f)
	{
		oldMousePosition = newMousePosition;
		return;
	}

	const float ROTATIONAL_SPEED = 0.5f;
	viewDirection = glm::mat3(glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, UP)) * viewDirection;
	glm::vec3 toRotateArouond = glm::cross(viewDirection, UP);
	glm::mat4 rotator = glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, UP) *
		glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED, toRotateArouond);

	viewDirection = glm::mat3(rotator) * viewDirection;

	oldMousePosition = newMousePosition;
}


glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}


Camera::~Camera()
{
}
