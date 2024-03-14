#include "Shader.h"

/* Self explanitory */
std::string getFileContents(const char* filename)
{
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
	throw(errno);
}

Shader::Shader(const char* vertFile, const char* fragFile)
{
	/* Read and store the shaderfile contents */
	std::string vertCode = getFileContents(vertFile);
	std::string fragCode = getFileContents(fragFile);

	/* String -> char array */
	const char* vertSource = vertCode.c_str();
	const char* fragSource = fragCode.c_str();

	/* Vertex and Fragment shader compiling */
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);
	compileErrors(vertShader, "VERTEX");
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);
	compileErrors(fragShader, "FRAGMENT");
	/* Wrap Vertex and Fragment shaders into a shader program */
	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
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

/* Checks if the selected shader has compiled properly */
void Shader::compileErrors(unsigned int shader, const char* type)
{
	/* Stores status of compilation */
	GLint hasCompiled;
	/* Character array to store error message */
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}