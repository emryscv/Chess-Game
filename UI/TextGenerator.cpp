#include "TextGenerator.h"

void TextGenerator::GenerateCharacters(FT_Face face) {

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // generate texture
        Texture glyph(face, GL_TEXTURE_2D);

        // now store character for later use
        Character character = {
            glyph,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters[c] = character;
    }
}

TextGenerator::TextGenerator(bool notDefault) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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

    FT_Set_Pixel_Sizes(face, 0, 48);
    GenerateCharacters(face);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    mTextShaderProgram = Shader("UI/Shaders/text.vert", "UI/Shaders/text.frag");

    mTextVAO = VAO(true);
    mTextVBO = VBO(NULL, sizeof(float) * 6 * 4, GL_DYNAMIC_DRAW);

    mTextVAO.LinkAttrib(mTextVBO, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    
    mTextVAO.Unbind();
    mTextVBO.Unbind();
}

void TextGenerator::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);

    mTextShaderProgram.Activate();
    glUniform3f(glGetUniformLocation(mTextShaderProgram.ID, "textColor"), color.x, color.y, color.z);
    glUniformMatrix4fv(glGetUniformLocation(mTextShaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    mTextVAO.Bind();
    mTextVBO.Bind();
   
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        ch.Glyph.Bind();
        // update content of VBO memory
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    Texture::Unbind(GL_TEXTURE_2D);
    mTextVBO.Unbind();
    mTextVAO.Unbind();
}
