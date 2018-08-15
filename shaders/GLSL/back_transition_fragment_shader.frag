#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D texturePreSampler;
uniform sampler2D textureMaskSampler;
uniform sampler2D texturePostSampler;
uniform float brightness;

void main()
{
    vec4 fragColorTmp = texture(textureSampler, texCoord);

	fragColorTmp.rgb += vec3(brightness, brightness, brightness);

	fragColor = fragColorTmp;
}
