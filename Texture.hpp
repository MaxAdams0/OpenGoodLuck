#include <vector>
#include <glad/glad.h>
#include <stb_image.h>

#ifndef TEXTURE_CLASS_HPP
#define TEXTURE_CLASS_HPP

class Texture {
public:
	unsigned int ID = 0;

	Texture(const char* filename, bool verticalFlip);
	void setParamsPS1();
};

#endif