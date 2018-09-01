#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;
out vec4 Position;
out mat4 orthoMat;

uniform mat4 projectionMat;

void main()
{
    gl_Position =projectionMat*vec4(position,0.0f,1.0f);
    TexCoord = texCoord;
    Position=gl_Position;
	orthoMat=projectionMat;
}