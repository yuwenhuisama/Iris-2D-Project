#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 desTexCoord;

out vec2 DesTexCoord;
out mat4 DesOthoMat;
out vec4 Position;

uniform mat4 desOthoMat;

void main()
{
    gl_Position = desOthoMat*vec4(position,0.0f,1.0f);
    DesTexCoord = desTexCoord;
	Position=gl_Position ;
	DesOthoMat=desOthoMat;
}