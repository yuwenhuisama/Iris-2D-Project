#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;

out vec2 texCoord;

uniform mat4 modelMat;
uniform mat4 projectionMat;
uniform vec2 orgPos;

void main() {
	vec4 posTmp = position;
	posTmp.xy -= orgPos;

    gl_Position = projectionMat * modelMat * posTmp;

	texCoord = textureCoord;
}
