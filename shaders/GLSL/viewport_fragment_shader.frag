#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D textureSampler;
uniform vec4 rect;
uniform ivec4 tone;

void main()
{
	vec4 outputColor = vec4(0, 0, 0, 0);
	vec2 texTmp = texCoord;

	if (texTmp.x > rect.x && texTmp.x < rect.z
		&& texTmp.y > rect.y && texTmp.y < rect.w) {

		outputColor = texture(textureSampler, texTmp);

		float grayFull = (outputColor.r * 38.0f + outputColor.g * 75.0f + outputColor.b * 15.0f) / 128.0f;
		outputColor.r = tone.r / 255.0f + outputColor.r + (grayFull - outputColor.r) * tone.a / 255.0f;
		outputColor.g = tone.g / 255.0f + outputColor.g + (grayFull - outputColor.g) * tone.a / 255.0f;
		outputColor.b = tone.b / 255.0f + outputColor.b + (grayFull - outputColor.b) * tone.a / 255.0f;
	}

	fragColor = outputColor;

}
