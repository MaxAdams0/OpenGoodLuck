#pragma once

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
	float fov;
	double yaw, pitch;
	float mouseSense;
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera(float fov, double yaw, double pitch, float mouseSense);
	void handleMouseInput(GLFWwindow* window, double x, double y);
};

#endif