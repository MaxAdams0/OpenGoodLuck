#include "Texture.hpp"
#include <glm/ext/vector_float3.hpp>

#ifndef ENTITY_CLASS_HPP
#define ENTITY_CLASS_HPP

struct Mesh {
	GLfloat* vertices;
	GLuint* indices;
};

class Entity {
private:
	glm::vec3 pos;
	glm::vec3 rot;
	Mesh mesh;
	Texture tex;

public:
	Entity(const char* pathname, GLfloat* vertices, GLuint* indices);
};

#endif
