#include "VAO.hpp"

VAO::VAO(GLenum type, std::vector<unsigned int> typesPerAttribute) {
	// Generating VAO object and binding it
	glGenVertexArrays(1, &this->ID);
	glBindVertexArray(this->ID);
	
	// Initializing & declaring data required but not in a VertexAttribute
	GLsizei stride = 0; // The total size of data required for one vertex attribute
	std::vector<GLsizei> offsets; // The size of data previous to this attribute
	for (int i = 0; i < typesPerAttribute.size(); i++) {
		// The amount of data preceeding this attribute. If it is the first attr., set = 0.
		(i != 0) ? offsets.emplace_back(stride) : offsets.emplace_back(0);
		GLsizei dataSize = typesPerAttribute.at(i) * sizeof(type);
		stride += dataSize; // Summing all the attribute's sizes to get the total
	}

	// Defining and enabling the vertex attributes
	for (int i = 0; i < typesPerAttribute.size(); i++) {
		glVertexAttribPointer(
			i, // nice & shrt
			typesPerAttribute.at(i),
			type,
			GL_FALSE, // 'Should the attribute be normalized?' Idk what this does tbh.
			stride,
			(void*)(offsets.at(i))
		);
		glEnableVertexAttribArray(i);
	}

	/*
		Yay! If you're wondering why it is so complicated, its so the dev has to do less work =)
		'The dev' being me.
		Yes, it is an abstraction, but its purpose is to free responsibility of 'the dev' for defining
			the properties correctly. Plus, most of this is just math. Computers should be good at that, right?
	*/
}
