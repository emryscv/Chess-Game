#version 330 core
in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D tex0;
uniform vec4 aColor;


void main()
{
   fragColor = texture(tex0, texCoords) * aColor;
}