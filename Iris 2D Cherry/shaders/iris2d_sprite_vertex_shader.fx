cbuffer cbChangesPerFrame: register(b0) {
	matrix posMatrix : packoffset(c0);
	matrix rotMatrix  : packoffset(c4);
	matrix zoomMatrix : packoffset(c8);
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
	vsOut.pos = mul(vertex.pos, zoomMatrix);
	vsOut.pos = mul(vsOut.pos, rotMatrix);
	vsOut.pos = mul(vsOut.pos, posMatrix);
	vsOut.pos = mul(vsOut.pos, viewProjMatrix);
	//vsOut.pos = mul(vertex.pos, viewProjMatrix);
	vsOut.tex0 = vertex.tex0;
	return vsOut;
}