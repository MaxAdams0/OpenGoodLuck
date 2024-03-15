#include <glad/glad.h>

#ifndef EBO_CLASS_HPP
#define EBO_CLASS_HPP

/*	Binding an object makes it the current "selected" object, where all tranformations will be localized
	Element Buffer Objects are objects which use indices to tell the rendering pipeline in what order the vertices are to be drawn */

class EBO {
public:
	/* Reference ID of the Element Buffer Object */
	GLuint ID;
	/*	Constructor which Generates EBO and binds it to the indices
		GLsizeiptr is what OpenGL uses for storing byte sizes */
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif