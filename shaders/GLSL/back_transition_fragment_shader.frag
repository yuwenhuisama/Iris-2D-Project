#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D texturePreSampler;
uniform sampler2D textureMaskSampler;
uniform sampler2D texturePostSampler;
uniform float brightness;
uniform float vague;
uniform float compare;
uniform int type;

void main()
{
	vec4 preColor = texture(texturePreSampler, texCoord);
	vec4 postColor = texture(texturePostSampler, texCoord);

	// fragColorTmp.rgb += vec3(brightness, brightness, brightness);

	vec4 fragColorTmp;

	if (type == 0) {
		vec4 maskColor = texture(textureMaskSampler, texCoord);
		fragColorTmp = preColor * (1.0f - compare) + postColor * compare;
	} else {
		vec4 maskColor = texture(textureMaskSampler, texCoord);
		float transV = maskColor.r;
		float cTransV = clamp(transV, compare, compare + vague);
		float alpha = (cTransV - compare) / vague;

		fragColorTmp = preColor * alpha + postColor * (1.0f - alpha);
	}

	fragColor = fragColorTmp;
}
