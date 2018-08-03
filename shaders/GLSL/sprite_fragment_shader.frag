#version 330 core
out vec4 fragColor;

in vec2 texCoord;

struct SpriteFragmentInfo {
	float opacity;
	int mirror;
};

uniform sampler2D textureSampler;
uniform SpriteFragmentInfo spriteFragmentInfo;

void main()
{
	vec2 texTmp = texCoord;
	if (spriteFragmentInfo.mirror == 1) {
		texTmp.x = 1.0f - texTmp.x;
	}

	fragColor = texture(textureSampler, texTmp);


	fragColor.a = spriteFragmentInfo.opacity;
}
