#pragma once

#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.hpp"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 texc;
};

struct TextureStruct {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	// Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureStruct> textures; // NOT TO BE CONFUSED WITH THE TEXTURE CLASS

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureStruct> textures);
	void Draw(Shader& shader);
private:
	// Render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};

#endif
