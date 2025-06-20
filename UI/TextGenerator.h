#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H 
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"

struct Character {
    Texture Glyph;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextGenerator
{
    VBO mTextVBO;
    VAO mTextVAO;

    Shader mTextShaderProgram;

    Character Characters[128];
   
    void GenerateCharacters(FT_Face face);

public:
    TextGenerator(bool notDefault);
    TextGenerator(){}

    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};

