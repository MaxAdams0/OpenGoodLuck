// Standard libraries
#include <iostream>
#include <numbers>
// The external libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
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

int window_width = 800;
int window_height = 800;
float camera_fov = 90.0f;

bool useWireframe = false;

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
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
// Initialize all libaries for use. Returns a GLFW window.
GLFWwindow* Initialize();
// For single key presses (toggles & not continues presses)
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	GLFWwindow* window = Initialize();

	VBO cubeVBO(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
	cubeVBO.Bind();
	VAO defaultVAO(GL_FLOAT, {3, 3, 2});
	cubeVBO.Unbind();
	EBO cubeEBO(indices, sizeof(indices), GL_DYNAMIC_DRAW);
	Shader defaultShader("default.vert.glsl", "default.frag.glsl");
	defaultShader.Use();
	Texture girlTex("girl.png", true);

	/* OpenGL uses a right-handed system. What is that? Do the physics hand thing but point your pointer up.
			each finger is pointing in the positive direction. Thumb = x, Pointer = y, Middle = z */
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 MVP = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f)); // move view back 3u
	projectionMatrix = glm::perspective(glm::radians(camera_fov), (float)window_width / (float)window_height, 0.1f, 100.0f);

	// The main event loop of the application
	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		// Whether or whether not to use wireframe mode
		(useWireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// Rendering stuff
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, girlTex.ID);

		float r = (sin(glfwGetTime() + 4) + 1.0f) / 2.0f;
		float g = (sin(glfwGetTime() + 2) + 1.0f) / 2.0f;
		float b = (sin(glfwGetTime() + 0) + 1.0f) / 2.0f;
		int vertexColorLocation = glGetUniformLocation(defaultShader.ID, "ourColor");
		glUseProgram(defaultShader.ID);
		glUniform3f(vertexColorLocation, r/2, g/2, b/2);

		defaultShader.Use();

		modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(0.2f), glm::vec3(0.1f, 1.0f, 0.1f));
		MVP = projectionMatrix * viewMatrix * modelMatrix;
		int mvpLoc = glGetUniformLocation(defaultShader.ID, "MVP"); // model view projection (I don't know why the acronym is out of order)
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		cubeEBO.Unlock();
		glDrawArrays(GL_TRIANGLES, 0, 36);

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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
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
	// Registers any window resize event to use the 'FramebufferSizeCallback' function
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	// Makes all key inputs go through the 'KeyCallback' function
	glfwSetKeyCallback(window, KeyCallback);

	return window;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) return; //only handle press events
	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_RIGHT_SHIFT) useWireframe = !useWireframe;
}