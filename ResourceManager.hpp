#include <vector>
#include "Shader.hpp"
#include "Texture.hpp"
#include "VAO.hpp"

#ifndef RESOURCEMANAGER_CLASS_HPP
#define RESOURCEMANAGER_CLASS_HPP

class ResourceManager {
private:
	std::vector<Shader*> shaders;
	std::vector<Texture*> textures;
	VAO standardVAO;
	VAO lightingVAO;

public:
	void createShader(const char* name, const char* vertFile, const char* fragFile);
	void createTexture(const char* image, const char* shaderName, GLenum format);

	void bindAllTextures();
	void activateAllShaders();

	void deleteAllTextures();
	void deleteAllShaders();

	Shader* getShaderByName(const char* name);
};

#endif