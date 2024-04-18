#pragma once

#ifndef EBO_CLASS_HPP
#define EBO_CLASS_HPP

#include <glad/glad.h>

/* Alternatives for the user. 'Locking data' can make more sense than
	'Unbinding the current object from operation flow' for naive devs. */
#define Unlock() Bind()
#define Lock() Unbind()

// Element Buffer Object Buffer Object. Allows for GPU to know what vertices form a triangle (indexing).
class EBO {
public:
	unsigned int ID = 0;

	EBO(const GLuint* indices, GLsizeiptr size, GLenum drawMethod);

	void Bind();
	void Unbind();
};

#endif