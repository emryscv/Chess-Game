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
   
    void GenerateCharacters(FT_Face face) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Characters[c] = character;
        }
    }

public:
	TextGenerator() {
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

		FT_Face face;
		if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return; // TODO if it returns here it might be a problem
		}
        
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

		FT_Set_Pixel_Sizes(face, 0, 48);
        GenerateCharacters(face);
	}
};

