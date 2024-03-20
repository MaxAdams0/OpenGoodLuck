#ifndef CAMERA_CLASS_HPP
#define CAMERA_CLASS_HPP

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include"Shader.hpp"

class Camera {
public:
	/* Self Explanitory Variables */
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 directUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	/* dimentions of the camera (viewport) */
	int width;
	int height;

	/* Travel speed and look sensitivity */
	float speed = 0.1f;
	float sens = 65.0f;

	Camera(int width, int height, glm::vec3 position);

	/* Create and send the view and projection matrixes to the vertex shader */
	void Matrix(Shader* shader, const char* uniform);
	/* Transform camera matrixes */
	void UpdateMatrix(float FOVdeg,  float nearPlane, float farPlane);
	/* Keyboard and mouse inputs */
		void Inputs(GLFWwindow* window);
};

#endif