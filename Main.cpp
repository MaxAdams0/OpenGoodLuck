// Standard libraries
#include <iostream>
// The external libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Then project files!
#include "Shader.hpp"

int window_width = 640;
int window_height = 640;

bool useWireframe = false;

// ctrl-f '// ERROR' to find places where error handling is needed

// These are in Normalized Device Coordinates (NDC), which are -1 to 1
float vertices[] = {
//          pos                color           tex
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f  // top left 
};
unsigned int indices[] = {  // note that we start from 0!
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

  // Tells the GPU how our vertex data is formatted
  unsigned int VAO; // Vertex Array Object
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  // Shoves all vertex data into one buffer to send to the GPU
  unsigned int VBO; // Vertex Buffer Object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Specify that we are using this object for vertexes
  /* For glBufferData, there are 3 ways to handle the data:
      GL_STREAM_DRAW: vertex data never changes, and is rarely used (rarely used)
      GL_STATIC_DRAW: vertex data never changes, but is used many times (basically, levels)
      GL_DYNAMIC_DRAW: vertex data changes frequently, and is used frequently (basically, entities)
  */
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Fill the VBO

  /* Explaination of each parameter in order:
      1. Which vertex attribute we want to set. For this project, pos=0,color=1,tex=2,normal=3
          The vertex shader's 'layout (location = 0)' means it is using the position attribute
      2. Size of vert.attr. (for pos, 3 bc a vec3 has 3 values)
      3. What type is contained in a vertex (GLSL's vec3 is floats)
      4. Should it be normalized (basically ignore this)
      5. Stride between vertices (the total storage required for one vertex attribute)
      6. Offset of this attribute from the first.
          EX: for color, offset = (void*)(3 * sizeof(float)) bc it is after the position attribute
  */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float))); // position attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // color attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texture attribute
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  // Allows for indexed drawing of triangles
  unsigned int EBO; // Element Buffer Object
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Create the shaders!
  Shader defaultShader("default.vert", "default.frag");

  // The main event loop of the application
  while (!glfwWindowShouldClose(window))
  {
    // Whether or whether not to use wireframe mode
    (useWireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Rendering stuff
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    defaultShader.Activate();

    float timeValue = glfwGetTime();
    float r = (sin(timeValue + 4) + 1.0f) / 2.0f;
    float g = (sin(timeValue + 2) + 1.0f) / 2.0f;
    float b = (sin(timeValue + 0) + 1.0f) / 2.0f;
    int vertexColorLocation = glGetUniformLocation(defaultShader.shaderProgramID, "ourColor");
    glUseProgram(defaultShader.shaderProgramID);
    glUniform3f(vertexColorLocation, r, g, b);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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