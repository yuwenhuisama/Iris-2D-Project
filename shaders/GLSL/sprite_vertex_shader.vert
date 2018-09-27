#version 330 core
// Vertex Attribute
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;

// Instance Attribute
layout (location = 2) in vec2 orgPos;
layout (location = 3) in float opacity;
layout (location = 4) in int mirror;
layout (location = 5) in vec4 rect;
layout (location = 6) in ivec4 tone;
layout (location = 7) in vec4 translateAndZoom;
layout (location = 8) in vec4 rotateMat1;
layout (location = 9) in vec4 rotateMat2;
layout (location = 10) in vec4 rotateMat3;
layout (location = 11) in vec4 rotateMat4;

out vec2 texCoord;
out float outOpacity;
flat out int outMirror;
out vec4 outRect;
flat out ivec4 outTone;

uniform mat4 projectionMat;

void main() {
	vec4 posTmp = position;
	posTmp.xy -= orgPos;

	mat4 rotateMat;

	rotateMat[0] = rotateMat1;
	rotateMat[1] = rotateMat2;
	rotateMat[2] = rotateMat3;
	rotateMat[3] = rotateMat4;

	posTmp.xy *= translateAndZoom.zw;
	gl_Position = rotateMat * posTmp;
	gl_Position.xy += translateAndZoom.xy;

	gl_Position = projectionMat * gl_Position;

	texCoord = textureCoord;
	outOpacity = opacity;
	outMirror = mirror;
	outRect = rect;
	outTone = tone;
}
