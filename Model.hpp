#ifndef MODEL_CLASS_HPP
#define MODEL_CLASS_HPP

#include <glad/glad.h>
#include <vector>
#include "Texture.hpp"

class Model {
public:
	GLfloat* cordVertices;
	GLfloat* colorVertices;
	GLfloat* texCoords;
	GLfloat* normCoords;
	GLint* indices;
	Texture* tex;

	/* White object with no texture */
	Model(
		GLfloat* cordVertices,
		GLint* cordIndices
	) {
		this->cordVertices = cordVertices;
		this->indices = indices;
	}
	/* Colored object with no texture*/
	Model(
		GLfloat* cordVertices,
		GLfloat* colorVertices,
		GLint* cordIndices
	) {
		this->cordVertices = cordVertices;
		this->colorVertices = colorVertices;
		this->indices = indices;
	}
	/* Textured object */
	Model(
		GLfloat* cordVertices,
		GLfloat* colorVertices,
		GLfloat* texCoords,
		GLfloat* normCoords,
		GLint* indices,
		Texture* tex
	) {
		this->cordVertices = cordVertices;
		this->colorVertices = colorVertices;
		this->texCoords = texCoords;
		this->normCoords = normCoords;
		this->indices = indices;
		this->tex = tex;
	}
};

#endif
