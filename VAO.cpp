#include "VAO.hpp"

/*
	What is a VAO (Vertex Array Object)?

	It is a container object that holds all the states needed to specify vertex data. 
	It encapsulates the setup and organization of vertex attribute pointers. 
	This allows you to define vertex data configurations once and reuse them efficiently 
	across multiple draw calls.
*/

/* Generates a VAO ID */
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

/*	Links a VBO to the VAO using the layout 
	Stride = byte size between two vertex attributes of the same type (i.e. XYZ, RGB, etc.) */
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}