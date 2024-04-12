#include "Texture.hpp"

Texture::Texture(const char* filename, bool verticalFlip) {
	// Load image using stb
	int width = 0, height = 0, channels = 0;
	stbi_set_flip_vertically_on_load(verticalFlip);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	// Generate texture in OpenGL
	glGenTextures(1, &this->ID);
	glBindTexture(GL_TEXTURE_2D, this->ID); // Binding tells OpenGL subsequent calls will update this type
	setParamsPS1();
	/* Parameter overview:
		2. mipmap level, 0 = base
		3. what image type OpenGL should store it as
		6. legacy stuff, ignore
		7. source image type
		8. image data type, ignore
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Free data (it won't be used, as the data is now stored with OpenGL in glTexImage2D())
	stbi_image_free(data);
}

void Texture::setParamsPS1() {
	// Setting texture rendering behavior. Nearest = pixel art, (Bi)linear = more realistic but blurry
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); // min = downscale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // mag = upscale
}