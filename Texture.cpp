#include <stb_image.h>
#include "Texture.hpp"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
{
	/* Assigns the type of the texture to the texture object */
	type = texType;

	int imgW, imgH, imgCh;
	stbi_set_flip_vertically_on_load(true);
	/* Reads image data and stores it as bytes */
	unsigned char* bytes = stbi_load(image, &imgW, &imgH, &imgCh, 0);

	/* Generates OpenGL Texture Object */
	glGenTextures(1, &ID);
	/* Assigns the texture to a Texture Unit */
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(texType, ID);
	/* Configures scaling behavior (Pixel) */
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/* Configures texture wraping behavior (Tile) */
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/* Utilize image data and bind it to the Texture Object */
	glTexImage2D(texType, 0, format, imgW, imgH, 0, format, pixelType, bytes);
	/*  Mimap generates small resolutions of the same image
		It is utilized for when minimal amounts of a texture are actally rendered */
	glGenerateMipmap(texType);
	/* Deletes the image data */
	stbi_image_free(bytes);
	/* Unbind to prevent accidental manipulation */
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	/* Gets the location of the uniform */
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	/* Shader needs to be activated before changing the value of a uniform */
	shader.Activate();
	/* Sets the value of the uniform */
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}