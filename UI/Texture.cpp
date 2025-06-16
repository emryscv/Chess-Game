#include "Texture.h"

void Texture::TextureSetUp(unsigned char* bytes, GLint internalFormat, GLsizei  width, GLsizei height, GLenum slot, GLenum format, GLenum pixelType, GLenum filter, GLenum wraper)
{
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(type, ID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, wraper);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, wraper);

	glTexImage2D(type, 0, internalFormat, width, height, 0, format, pixelType, bytes);
	glGenerateMipmap(type);

	glBindTexture(type, 0);
}

Texture::Texture(const char* image, GLenum texType)
{
	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
	
	TextureSetUp(bytes, GL_RGBA, widthImg, heightImg, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);

	stbi_image_free(bytes);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{

	glDeleteTextures(1, &ID);
}
