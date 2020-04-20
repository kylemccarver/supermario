#version 330 core
layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 vColor;

out vec4 color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * pos;
    color = vColor;
    TexCoord = texCoord;
}
