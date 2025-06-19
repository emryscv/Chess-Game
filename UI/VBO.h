#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID;
	VBO() : ID(0) {}
	VBO(GLfloat* vertices, GLsizeiptr size, GLenum usage);

	void Bind();
	void Unbind();
	void Delete();
};

#endif