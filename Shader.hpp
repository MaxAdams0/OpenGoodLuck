#pragma once

#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>
#include "Errornter.hpp"

#define Use() Activate()

class Shader {
public:
	/* The shader program's ID number given by glCreateProgram() */
	unsigned int ID;

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

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
};

#endif