cbuffer cbChangesPerFrame: register(b0) {
	matrix posMatrix : packoffset(c0);
	float ox : packoffset(c4.x);
	float oy : packoffset(c4.y);
};

cbuffer cbChangesOnResize : register(b1) {
	matrix viewProjMatrix;
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
	vsOut.pos = vertex.pos;
	vsOut.pos.x -= ox;
	vsOut.pos.y -= oy;

	vsOut.pos = mul(vsOut.pos, posMatrix);
	vsOut.pos = mul(vsOut.pos, viewProjMatrix);

	vsOut.tex0 = vertex.tex0;

	return vsOut;
}