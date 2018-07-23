#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoord;

out vec2 texCoord;

void main() {
    gl_Position = position;

	texCoord = textureCoord;
}
