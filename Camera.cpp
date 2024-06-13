#include "Camera.hpp"

Camera::Camera(float fov, double yaw, double pitch, float mouseSense) {
	this->fov = fov;
	this->yaw = yaw;
	this->pitch = pitch;
	this->mouseSense = mouseSense;
}

void Camera::handleMouseInput(GLFWwindow* window, double x, double y) {
	glfwGetCursorPos(window, &x, &y);

	double dx = x * this->mouseSense;
	double dy = -y * this->mouseSense;

	this->yaw += dx;
	this->pitch += dy;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(this->front);

	glfwSetCursorPos(window, 0, 0);
}