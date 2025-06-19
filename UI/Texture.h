#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H 

#include "shaderClass.h"

class Texture
{
	void TextureSetUp(unsigned char* bytes, GLint internalFormat, GLsizei  width, GLsizei height, GLenum slot, GLenum format, GLenum pixelType, GLenum filter, GLenum wraper);

public:
	GLuint ID;
	GLenum type;
	Texture() : ID(0), type(GL_TEXTURE_2D) {}
	Texture(const char* image, GLenum texType);
	Texture(FT_Face face, GLenum texType);

	void texUnit(Shader shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

	static void Unbind(GLenum type);
};

#endif


