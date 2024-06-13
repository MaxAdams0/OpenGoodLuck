// Standard libraries
#include <iostream>
#include <numbers>
// The external libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Then project files!
#include "Shader.hpp"
#include "Errornter.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Util.hpp"
#include "Model.hpp"

int window_width = 800;
int window_height = 800;

bool useWireframe = false;

Camera cam(90.0f, 0.0f, 0.0f, 0.1f);

// ctrl-f '// ERROR' to find places where error handling is needed

// When I get textures obj loader working, this will be replaced by 'dev\modelsnstuff\bluemorpho\BlueMorpho.obj'
// These are in Normalized Device Coordinates (NDC), which are -1 to 1
GLfloat vertices[] = {
//			pos					  color				tex
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f
};
GLuint indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

// For resizing the window
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
// Initialize all libaries for use. Returns a GLFW window.
GLFWwindow* Initialize();
// For single key presses (toggles & not continues presses)
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
// Camera shenanigans
void processInput(GLFWwindow* window, float deltaTime);

void mousePosCallback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	GLFWwindow* window = Initialize();

	Shader defaultShader("default.vert.glsl", "default.frag.glsl");
	defaultShader.Use();

	std::string butterflyPath = "E:/dev/OpenGoodLuck/res/bluemorpho/BlueMorpho.gltf";
	Model butterfly(butterflyPath.c_str());

	/* OpenGL uses a right-handed system. What is that? Do the physics hand thing but point your pointer up.
			each finger is pointing in the positive direction. Thumb = x, Pointer = y, Middle = z */
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 MVP = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(cam.fov), (float)window_width / (float)window_height, 0.1f, 100.0f);

	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;

	// The main event loop of the application
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrameTime;
		lastFrameTime = currentFrame;

		float time = glfwGetTime();
		// Whether or whether not to use wireframe mode
		(useWireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Rendering stuff
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		float r = (sin(glfwGetTime() + 4) + 1.0f) / 2.0f;
		float g = (sin(glfwGetTime() + 2) + 1.0f) / 2.0f;
		float b = (sin(glfwGetTime() + 0) + 1.0f) / 2.0f;
		int vertexColorLocation = glGetUniformLocation(defaultShader.ID, "ourColor");
		glUseProgram(defaultShader.ID);
		glUniform3f(vertexColorLocation, r/2, g/2, b/2);
		*/

		int vertexColorLocation = glGetUniformLocation(defaultShader.ID, "ourColor");
		glUseProgram(defaultShader.ID);
		glUniform3f(vertexColorLocation, 1.0f, 1.0f, 1.0f);

		processInput(window, deltaTime);
		viewMatrix = glm::lookAt(cam.pos, cam.pos + cam.front, cam.up);

		defaultShader.Use();
		//modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(0.2f), glm::vec3(0.1f, 1.0f, 0.1f));
		MVP = projectionMatrix * viewMatrix * modelMatrix;
		int mvpLoc = glGetUniformLocation(defaultShader.ID, "MVP"); // model view projection (I don't know why the acronym is out of order)
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));
		butterfly.Draw(defaultShader);


		/* Swaps the color buffer(a large 2D buffer that contains color values for each pixel).
			Rendering applications have a Double Buffer. If apps were to render moment-to-moment,
			there would be flickering because it takes time for the applcation to draw the image,
			but making one a draw-to and one a final image, and then swaping, fixes that problem.
		*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate(); // So long, gay bowser!
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* Initialize() {
	// Initializing GLFW - used for window creation and inputs
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // the 1st 3 in v3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // the 2nd 3 in v3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGoodLuck", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		// ERROR
	}

	glfwMakeContextCurrent(window);

	// Initializing GLAD - used for OpenGL function pointers and OS-level stuff
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		// ERROR
	}
	glViewport(0, 0, window_width, window_height);
	// Registers any window resize event to use the 'framebufferSizeCallback' function
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	// Makes all key inputs go through the 'KeyCallback' function
	glfwSetKeyCallback(window, keyCallback);
	// Mouse stuff
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) return; //only handle press events
	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_RIGHT_SHIFT) useWireframe = !useWireframe;
}

void processInput(GLFWwindow* window, float deltaTime)
{
	const float cameraSpeed = 0.1f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cam.pos += cameraSpeed * cam.front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cam.pos -= cameraSpeed * cam.front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cam.pos -= glm::normalize(glm::cross(cam.front, cam.up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cam.pos += glm::normalize(glm::cross(cam.front, cam.up)) * cameraSpeed;
}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	cam.handleMouseInput(window, xpos, ypos);
}