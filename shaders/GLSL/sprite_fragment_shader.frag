#version 330 core
out vec4 fragColor;

in vec2 texCoord;

struct SpriteFragmentInfo {
	float opacity;
	int mirror;
	vec4 rect;
	ivec4 tone;
};

uniform sampler2D textureSampler;
uniform SpriteFragmentInfo spriteFragmentInfo;

void main()
{
	vec4 outputColor = vec4(0, 0, 0, 0);
	vec2 texTmp = texCoord;

	if (texTmp.x > spriteFragmentInfo.rect.x && texTmp.x < spriteFragmentInfo.rect.z
		&& texTmp.y > spriteFragmentInfo.rect.y && texTmp.y < spriteFragmentInfo.rect.w) {
		if (spriteFragmentInfo.mirror == 1) {
			texTmp.x = 1.0f - texTmp.x;
		}
		outputColor = texture(textureSampler, texTmp);

		float grayFull = (outputColor.r * 38.0f + outputColor.g * 75.0f + outputColor.b * 15.0f) / 128.0f;
		outputColor.r = spriteFragmentInfo.tone.r / 255.0f + outputColor.r + (grayFull - outputColor.r) * spriteFragmentInfo.tone.a / 255.0f;
		outputColor.g = spriteFragmentInfo.tone.g / 255.0f + outputColor.g + (grayFull - outputColor.g) * spriteFragmentInfo.tone.a / 255.0f;
		outputColor.b = spriteFragmentInfo.tone.b / 255.0f + outputColor.b + (grayFull - outputColor.b) * spriteFragmentInfo.tone.a / 255.0f;
		
		outputColor.a = spriteFragmentInfo.opacity;
	}

	fragColor = outputColor;
}
