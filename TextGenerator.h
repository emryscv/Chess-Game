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

struct Character {
    Texture TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextGenerator
{
    Character Characters[128];
   
	void GenerateCharacters(FT_Face face);

public:
    TextGenerator();
};

