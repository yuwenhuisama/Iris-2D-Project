#version 330 core
out vec4 fragColor;

in vec2 texCoord;
in float outOpacity;
flat in int outMirror;
in vec4 outRect;
flat in ivec4 outTone;

uniform sampler2D textureSampler;

void main()
{
	vec4 outputColor = vec4(0, 0, 0, 0);
	vec2 texTmp = texCoord;

	if (texTmp.x > outRect.x && texTmp.x < outRect.z
		&& texTmp.y > outRect.y && texTmp.y < outRect.w) {
		if (outMirror == 1) {
			texTmp.x = 1.0f - texTmp.x;
		}
		outputColor = texture(textureSampler, texTmp);

		float grayFull = (outputColor.r * 38.0f + outputColor.g * 75.0f + outputColor.b * 15.0f) / 128.0f;
		outputColor.r = outTone.r / 255.0f + outputColor.r + (grayFull - outputColor.r) * outTone.a / 255.0f;
		outputColor.g = outTone.g / 255.0f + outputColor.g + (grayFull - outputColor.g) * outTone.a / 255.0f;
		outputColor.b = outTone.b / 255.0f + outputColor.b + (grayFull - outputColor.b) * outTone.a / 255.0f;
		
		outputColor.a = outputColor.a * outOpacity;
	}

	fragColor = outputColor;
}
