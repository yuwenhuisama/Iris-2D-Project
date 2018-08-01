#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;

out vec2 texCoord;

struct SpriteInfo {
	mat4 translateMat;
	mat4 rotationMat;
	mat4 zoomMat;
	vec2 orgPos;
	float opacity;
	int mirror;
};

uniform mat4 projectionMat;
uniform SpriteInfo spriteInfo;

void main() {
    gl_Position = projectionMat * position;

	texCoord = textureCoord;
}
