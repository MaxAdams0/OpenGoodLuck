#include "Shader.hpp"

Shader::Shader(const char* vertFile, const char* fragFile)
{
	unsigned int vertShader = CreateShader(vertFile, GL_VERTEX_SHADER);
	unsigned int fragShader = CreateShader(fragFile, GL_FRAGMENT_SHADER);
	CreateShaderProgram(vertShader, fragShader);
}

unsigned int Shader::CreateShader(const char* filename, int shaderType) {
	/* Read and store the shaderfile contents */
	std::string code = "";
	try {
		code = FileToString(filename);
	}
	catch (int errorcode) {
		std::string strFilename;
		strFilename.append(filename);
		Errornter::coutErrorCode(errorcode, "thrown @ Shader::FileToString, file='" + strFilename + "'");
	}
	
	const char* src = code.c_str();

	// Verify that the given type is valid 
	bool valid = (shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER) ? true : false;
	if (!valid) {
		std::cout << "ERROR::SHADER::INVALID_SHADER_TYPE" << std::endl;
	}
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	return shader;
}

void Shader::CreateShaderProgram(unsigned int vertShader, unsigned int fragShader) {
	/* Wrap Vertex and Fragment shaders into a shader program */
	this->ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);

	/* Check if the shader program has any errors linking */
	int  success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::FAILED\n" << infoLog << std::endl;
	}

	/* Delete both shaders (since they are already linked) */
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

std::string Shader::FileToString(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();

		return(contents);
	}
	throw(ERROR_FILENOTEXIST);
}

void Shader::SetBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}