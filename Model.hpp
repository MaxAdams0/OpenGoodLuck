#ifndef MODEL_CLASS_HPP
#define MODEL_CLASS_HPP

#include <glad/glad.h>
#include <vector>
#include "Texture.hpp"

class Model {
private:
	GLfloat* vertices;
	GLuint* indices;

public:
	Model(GLfloat* vertices, GLuint* indices) {
		this->vertices = vertices;
		this->indices = indices;
	}
};

#endif
