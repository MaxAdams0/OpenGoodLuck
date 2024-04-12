#include <vector>
#include <glad/glad.h>

#ifndef VAO_CLASS_HPP
#define VAO_CLASS_HPP

// Vertex Array Object. Tells the GPU how our vertex data is formatted, per object, per multiple objects or globally.
class VAO { 
public:
	unsigned int ID = 0;

	VAO(GLenum type, std::vector<unsigned int>);
};

#endif