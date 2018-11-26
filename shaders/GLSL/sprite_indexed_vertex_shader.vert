#version 330 core
// Vertex Attribute
layout (location = 0) in vec4 position;

// Instance Attribute
layout (location = 1) in vec4 textureCoord12;
layout (location = 2) in vec4 textureCoord34;
layout (location = 3) in vec2 orgPos;
layout (location = 4) in float opacity;
layout (location = 5) in int mirror;
layout (location = 6) in vec4 rect;
layout (location = 7) in ivec4 tone;
layout (location = 8) in vec4 translateAndZoom;
layout (location = 9) in vec4 rotateMat1;
layout (location = 10) in vec4 rotateMat2;
layout (location = 11) in vec4 rotateMat3;
layout (location = 12) in vec4 rotateMat4;

out vec2 texCoord;
out float outOpacity;
flat out int outMirror;
out vec4 outRect;
flat out ivec4 outTone;

uniform mat4 projectionMat;

const vec2 c_coords[] = vec2[] (
	vec2(1.0f, 1.0f), vec2(1.0f, 0.0f), 
	vec2(0.0f, 0.0f), vec2(0.0f, 1.0f)
);

void main() {
	vec4 posTmp = position;
	posTmp.xy -= orgPos;

	mat4 rotateMat;

	vec2 coords[] = vec2[] (
		textureCoord12.xy, textureCoord12.zw, 
		textureCoord34.xy, textureCoord34.zw
	);

	rotateMat[0] = rotateMat1;
	rotateMat[1] = rotateMat2;
	rotateMat[2] = rotateMat3;
	rotateMat[3] = rotateMat4;

	posTmp.xy *= translateAndZoom.zw;
	gl_Position = rotateMat * posTmp;
	gl_Position.xy += translateAndZoom.xy;

	gl_Position = projectionMat * gl_Position;

	texCoord = coords[gl_VertexID];

	outOpacity = opacity;
	outMirror = mirror;
	outRect = rect;
	outTone = tone;
}
