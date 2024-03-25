#include "Shader.hpp"

Shader::Shader(const char* vertFile, const char* fragFile)
{
	unsigned int vertShader = CreateShader(vertFile, GL_VERTEX_SHADER);
	unsigned int fragShader = CreateShader(fragFile, GL_FRAGMENT_SHADER);
	CreateShaderProgram(vertShader, fragShader);
}

unsigned int Shader::CreateShader(const char* filename, int shaderType) {
	/* Read and store the shaderfile contents */
	const char* code = FileToCString(filename);

	/* Verify that the given type is valid 
		TODO: This is a very convoluted way to do it. Think of something better later on.	
	*/
	bool valid = (shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER) ? true : false;
	if (!valid) {
		std::cout << "ERROR::SHADER::INVALID_SHADER_TYPE" << std::endl;
	}
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	/* Check if the file has any errors while compiling */
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderTypes[shaderType] << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::CreateShaderProgram(unsigned int vertShader, unsigned int fragShader) {
	/* Wrap Vertex and Fragment shaders into a shader program */
	this->shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertShader);
	glAttachShader(shaderProgramID, fragShader);
	glLinkProgram(shaderProgramID);

	/* Check if the shader program has any errors linking */
	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Delete both shaders (since they are already linked) */
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::Activate()
{
	glUseProgram(shaderProgramID);
}

void Shader::Delete()
{
	glDeleteProgram(shaderProgramID);
}

const char* Shader::FileToCString(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();

		return(contents.c_str());
	}
	throw(errno);
}