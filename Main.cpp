// Standard libraries
#include <iostream>
// The external libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Then project files!
#include "Shader.hpp"

int window_width =  800;
int window_height = 600;

// ctrl-f '// ERROR' to find places where error handling is needed

// These are in Normalized Device Coordinates (NDC), which are -1 to 1
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

// Provides instruction for any key press as the window is displayed.
void processInput(GLFWwindow* window);
// Resizing the window.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Initialize all libaries for use. Returns a GLFW window.
GLFWwindow* initialize();

int main()
{
	GLFWwindow* window = initialize();

	// Shoves all vertex data into one buffer to send to the GPU
	unsigned int VBO; // VBO = Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Specify that we are using this object for vertexes
	/* For glBufferData, there are 3 ways to handle the data: 
		GL_STREAM_DRAW: vertex data never changes, and is rarely used (rarely used)
		GL_STATIC_DRAW: vertex data never changes, but is used many times (basically, levels)
		GL_DYNAMIC_DRAW: vertex data changes frequently, and is used frequently (basically, entities)
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Fill the VBO

	Shader defaultShaders("default.vert", "default.frag");
	defaultShaders.Activate();

	// The main event loop of the application
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// Rendering stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
GLFWwindow* initialize() {
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
	// Registers any window resize event to use the 'framebuffer_size_callback' function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}