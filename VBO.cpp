#include "VBO.hpp"

VBO::VBO(const GLfloat* vertices, GLsizeiptr size, GLenum drawMethod) {
	glGenBuffers(1, &this->ID);
	Bind();
	/* For glBufferData, there are 3 ways to handle the data:
		GL_STREAM_DRAW: vertex data never changes, and is rarely used (basically nothing)
		GL_STATIC_DRAW: vertex data never changes, but is used many times (basically, most things)
		GL_DYNAMIC_DRAW: vertex data changes frequently, and is used frequently (basically, entities with deformations)
	*/
	glBufferData(GL_ARRAY_BUFFER, size, vertices, drawMethod); // Fill the VBO
	Unbind();
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}