#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Model.hpp"

#ifndef ENTITY_CLASS_HPP
#define ENTITY_CLASS_HPP

class Entity
{
public:
	std::string name;
	glm::vec3 pos;
	glm::vec3 rot;
	Model* model;

	/* For use in points with no visuals */
	Entity(std::string name, glm::vec3 pos, glm::vec3 rot) {
		this->name = name;
		this->pos = pos;
		this->rot = rot;
	}
	/* For usual objects */
	Entity(std::string name, glm::vec3 pos, glm::vec3 rot, Model* model) {
		this->name = name;
		this->pos = pos;
		this->rot = rot;
		this->model = model;
	}

	void Translate();
	void Rotate();
};
#endif