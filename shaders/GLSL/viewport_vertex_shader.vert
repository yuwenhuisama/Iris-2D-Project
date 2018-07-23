#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertecColor;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vertecColor = vec4(0.5, 0.0, 0.0, 1.0);
}