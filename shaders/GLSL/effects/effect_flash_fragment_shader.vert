#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform vec4 targetColor;
uniform vec2 counter;

uniform sampler2D textureSampler;

void main()
{
    vec4 textureColor = texture(textureSampler, texCoord);

	fragColor = textureColor + (targetColor - textureColor) * (counter.x / counter.y);
}
