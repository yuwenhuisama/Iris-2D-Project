cbuffer cbChangesPerFrame: register(b0) {
	matrix mvp;
};

struct VS_Input {
	float4 pos: POSITION;
	float2 tex0: TEXCOORD0;
};

struct PS_Input {
	float4 pos: SV_POSITION;
	float2 tex0: TEXCOORD0;
};

PS_Input VSMain(VS_Input vertex) {
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, mvp);
	vsOut.tex0 = vertex.tex0;
	return vsOut;
}