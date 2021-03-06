#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D textureSampler;
uniform float brightness;
uniform vec2 fadeInfo;

void main()
{
    vec4 fragColorTmp = texture(textureSampler, texCoord);

	fragColorTmp.rgb += vec3(brightness, brightness, brightness);

	fragColorTmp.rgba = fragColorTmp.rgba * fadeInfo.x / fadeInfo.y;

	fragColor = fragColorTmp;
}
