#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) 
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	view = glm::lookAt(Position, Position + Orientation, directUp);
	proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);
	
	cameraMatrix = proj * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	/* glm::value_ptr points to the object itself, not the data in it */
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
	/* Keyboard */
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, directUp));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, directUp));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * directUp;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) 
	{
		Position += speed * -directUp;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.05f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.02f;
	}
	/* Mouse */
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (firstClick == true) {
			glfwSetCursorPos(window, ((float)width / 2), ((float)height / 2));
			firstClick = false;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		float rotX = sens * (float)(mouseY - ((float)height / 2)) / height;
		float rotY = sens * (float)(mouseX - ((float)height / 2)) / height;
		glm::vec3 newOrient = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, directUp)));
		if (!(glm::angle(newOrient, directUp) <= glm::radians(5.0f) || glm::angle(newOrient, -directUp) <= glm::radians(5.0f))) {
			Orientation = newOrient;
		}
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), directUp);
		glfwSetCursorPos(window, ((float)width / 2), ((float)height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}