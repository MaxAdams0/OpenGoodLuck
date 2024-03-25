#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <glad/glad.h>

#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

class Shader {
public:
	/* The ID # given by glCreateProgram() */
	int shaderProgramID;

	/* Constructor which creates the vertex and fragment shaders, then a shader program */
	Shader(const char* vertFile, const char* fragFile);

	/* Create a new shader */
	unsigned int CreateShader(const char* filename, int shaderType);
	/* Link the vertex shader and fragment shader into one */
	void CreateShaderProgram(unsigned int vertShader, unsigned int fragShader);
	/* Tell OpenGL to use the shaders during the GPU process */
	void Activate();
	/* Delete the ShaderProgram and its child shaders */
	void Delete();
	/* General util function for converting a file to an array of chars */
	std::string FileToString(const char* filename);
};

#endif