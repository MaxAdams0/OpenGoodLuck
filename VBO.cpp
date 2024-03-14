#include "VBO.h"

/*
	What is a VBO (Vertex Buffer Object)?

	It is a buffer that holds vertex data such as positions, colors, or texture coordinates. 
	It efficiently stores this data on the GPU, allowing for faster rendering by reducing the 
	need to transfer data between the CPU and GPU during draw calls.
*/

/*	Generated VBO and binds it to the vertices
	GLsizeiptr is what OpenGL uses for storing byte sizes*/
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}