#version 330 core
in vec4 color;
in vec2 TexCoord;
out vec4 fragment_color;

uniform sampler2D ourTexture;

void main()
{
    fragment_color = texture(ourTexture, TexCoord);
}
