Texture2D colorMap: register(t0);
SamplerState colorSampler: register(s0);

cbuffer cbChangesPerFrame: register(b0) {
	float4 rect : packoffset(c0);
	float4 tone : packoffset(c1);
}

struct PS_Input {
	float4 pos: SV_POSITION;
	float2 tex0: TEXCOORD0;
};

float4 PSMain(PS_Input frag) : SV_TARGET {
	float4 color = (float4)0;

	// Cut
	if ((frag.tex0.x < rect.x || frag.tex0.x > rect.z)
		|| (frag.tex0.y < rect.y || frag.tex0.y > rect.w)) {
		color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else {
		color = colorMap.Sample(colorSampler, frag.tex0);
		// Tone
		float grayFull = (color.r * 38.0f + color.g * 75.0f + color.b * 15.0f) / 128.0f;
		color.r = tone.r / 255.0f + color.r + (grayFull - color.r) * tone.a / 255.0f;
		color.g = tone.g / 255.0f + color.g + (grayFull - color.g) * tone.a / 255.0f;
		color.b = tone.b / 255.0f + color.b + (grayFull - color.b) * tone.a / 255.0f;
	}
	
	return color;
}