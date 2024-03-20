#include "ResourceManager.hpp"

void ResourceManager::createShader(const char* name, const char* vertFile, const char* fragFile) {
	Shader newShader(name, vertFile, fragFile);
	this->shaders.emplace_back(&newShader);
};

void ResourceManager::createTexture(const char* image, const char* shaderName, GLenum format) {
	Shader* usingShader = getShaderByName(shaderName);
	Texture newTex(image, GL_TEXTURE_2D, this->textures.size(), format, GL_UNSIGNED_BYTE);

	const char uniNum = static_cast<char>(this->textures.size());
	const char uniform = strcmp("tex", &uniNum);
	newTex.texUnit(usingShader, &uniform);

	this->textures.emplace_back(&newTex);
};

void ResourceManager::bindAllTextures() {
	for (Texture* tex : this->textures) {
		tex->Bind();
	}
};

void ResourceManager::deleteAllTextures() {
	for (Texture* tex : this->textures) {
		tex->Delete();
	}
};

void ResourceManager::activateAllShaders() {
	for (Shader* shader : this->shaders) {
		shader->Activate();
	}
};

void ResourceManager::deleteAllShaders() {
	for (Shader* shader : this->shaders) {
		shader->Delete();
	}
};

Shader* ResourceManager::getShaderByName(const char* name) {
	for (Shader* shader : this->shaders) {
		if (strcmp(shader->name, name) == 0) {
			return shader;
		}
	}
	// ERROR CHECKING TODO: INVALID SHADER RESULTS IN UNWANTED BEHAVIOR
	return this->shaders.front();
};