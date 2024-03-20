#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>
#include "Camera.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "ResourceManager.hpp"

/*
	A lot of the basic core fucntions in the engine are derived from
	https://www.youtube.com/watch?v=45MIykWJ-C4&t=237s
	The rest is mine, just to clarify =)
*/

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

const unsigned int winResW = 800;
const unsigned int winResH = 800;

int main(void)
{
	/* Initialize the library */
	glfwInit();
	/* Initialize the window context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(winResW, winResH, "OpenGL Render Window", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	/* Specify the viewport of OpenGL in the Window
	In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800 */
	glViewport(0, 0, winResW, winResH);

	/* All the good shader stuff. Actual help in their respective files =) */
	ResourceManager RM;
	RM.createShader("default", "default.vert", "default.frag");
	RM.createShader("light", "light.vert", "light.frag");
	RM.createTexture("planks.png", "default", GL_RGBA);
	RM.createTexture("planksSpec.png", "default", GL_RED);

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	/* Links VBO attributes (i.e. coord, color, texture coords, etc.) */
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)(0));
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	/* Unbind to prevent accidental manipulation */
	VBO1.Unbind();
	EBO1.Unbind();
	VAO1.Unbind();

	/* Shader for light object */
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	RM.getShaderByName("light")->Activate();
	glUniformMatrix4fv(glGetUniformLocation(RM.getShaderByName("light")->ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(RM.getShaderByName("light")->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	RM.getShaderByName("default")->Activate();
	glUniformMatrix4fv(glGetUniformLocation(RM.getShaderByName("default")->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(RM.getShaderByName("default")->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(RM.getShaderByName("default")->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	/* Enable the depth buffer */
	glEnable(GL_DEPTH_TEST);
	/* Screen width & height, starting positions */
	Camera camera(winResW, winResH, glm::vec3(0.0f, 0.5f, 3.0f));

	while (!glfwWindowShouldClose(window))
	{
		RM.bindAllTextures();
		RM.activateAllShaders();

		/* Background color */
		glClearColor(0.04f, 0.10f, 0.22f, 1.0f);
		/* Clear the back buffer and assign new color */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* Handle keyboard & mouse inputs */
		camera.Inputs(window);
		/* Update camera perspective */
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		/* Identify shader */
		glUniform3f(glGetUniformLocation(RM.getShaderByName("default")->ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(RM.getShaderByName("default"), "camMatrix");
		/* Bind VAO for use */
		VAO1.Bind();
		/* Geometrical primitive, indices count, datatype of indices, index of indices */
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		camera.Matrix(RM.getShaderByName("light"), "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		/* Swap back/front buffers */
		glfwSwapBuffers(window);

		/* Monitor GLFW events (like close window) */
		glfwPollEvents();
	}

	/* RIP AND TEAR UNTIL ALL OF THE MEMORY IS DESTROYED */
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	RM.deleteAllShaders();
	RM.deleteAllTextures();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}