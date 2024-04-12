#include <glad/glad.h>

#ifndef VBO_CLASS_HPP
#define VBO_CLASS_HPP

/* Alternatives for the user. 'Locking data' can make more sense than
	'Unbinding the current object from operation flow' for naive devs. */
#define Unlock() Bind()
#define Lock() Unbind()

// Vertex Buffer Object. Shoves all vertex data into one buffer to send to the GPU.
class VBO {
public:
	unsigned int ID = 0;

	VBO(const GLfloat* vertices, GLsizeiptr size, GLenum drawMethod);

	void Bind();
	void Unbind();
};

#endif