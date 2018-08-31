#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position,0.f,1.0f);
    TexCoord = texCoord;
}