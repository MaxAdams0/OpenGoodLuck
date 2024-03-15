#include <glad/glad.h>
#include "VBO.hpp"

#ifndef VAO_CLASS_HPP
#define VAO_CLASS_HPP

/*	Binding an object makes it the current "selected" object, where all tranformations will be localized
	Vertex Array Buffers point towards VBOs and tells OpenGL how to interperate them to render */

class VAO {
public:
	/* Reference ID of the Vertex Array Object */
	GLuint ID;
	/* Constructor which Generates a VAO ID */
	VAO(); // Constructor

	/* Links a VBO to the VAO using a the layout */
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};
#endif
