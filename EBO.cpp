#include "EBO.hpp"

EBO::EBO(const GLuint* indices, GLsizeiptr size, GLenum drawMethod) {
	glGenBuffers(1, &ID);
	Bind();
	/* For glBufferData, there are 3 ways to handle the data:
		GL_STREAM_DRAW: vertex data never changes, and is rarely used (basically nothing)
		GL_STATIC_DRAW: vertex data never changes, but is used many times (basically, most things)
		GL_DYNAMIC_DRAW: vertex data changes frequently, and is used frequently (basically, entities with deformations)
	*/
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, drawMethod); // Fill the EBO
	Unbind();
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}