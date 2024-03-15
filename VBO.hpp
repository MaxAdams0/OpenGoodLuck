#include <glad/glad.h>

#ifndef VBO_CLASS_HPP
#define VBO_CLASS_HPP

/*	Binding an object makes it the current "selected" object, where all tranformations will be localized 
	Vertex Buffer Objectss are objects containing the manipulated vertice data(?) */

class VBO {
public:
	/* Reference ID of the Vertex Buffer Object */
	GLuint ID;
	/*	Constructor which Generates VBO and binds it to the vertices
		GLsizeiptr is what OpenGL uses for storing byte sizes */
	VBO(GLfloat* vertices, GLsizeiptr size); // Constructor

	void Bind();
	void Unbind();
	void Delete();
};

#endif