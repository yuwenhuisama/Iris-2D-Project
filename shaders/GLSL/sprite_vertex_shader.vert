#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;

out vec2 texCoord;

struct SpriteVertexInfo {
	mat4 translateMat;
	mat4 rotationMat;
	mat4 zoomMat;
	vec2 orgPos;
};

uniform mat4 projectionMat;
uniform SpriteVertexInfo spriteVertexInfo;

void main() {
	vec4 posTmp = position;
	posTmp.xy -= spriteVertexInfo.orgPos;

    gl_Position = projectionMat * spriteVertexInfo.translateMat * spriteVertexInfo.rotationMat* spriteVertexInfo.zoomMat * posTmp;

	texCoord = textureCoord;
}
