#include <glad/glad.h>
#include <stb_image.h>
#include "Shader.hpp"

#ifndef TEXTURE_CLASS_HPP
#define TEXTURE_CLASS_HPP

class Texture {
public:
	/* Reference ID */
	GLuint ID;
	GLenum type;
	GLuint unit;
	Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

	/* Assigns a texture unit to a texture */
	void texUnit(Shader* shader, const char* uniform);
	void Bind();
	void Unbind();
	void Delete();
};
#endif