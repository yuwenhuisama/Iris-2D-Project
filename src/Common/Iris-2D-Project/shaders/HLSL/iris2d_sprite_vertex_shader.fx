cbuffer cbChangesPerFrame: register(b0) {
	matrix posMatrix : packoffset(c0);
	matrix rotMatrix  : packoffset(c4);
	matrix zoomMatrix : packoffset(c8);
	float ox : packoffset(c12.x);
	float oy : packoffset(c12.y);
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

	vsOut.pos = mul(vsOut.pos, rotMatrix);
	vsOut.pos = mul(vsOut.pos, zoomMatrix);
	vsOut.pos = mul(vsOut.pos, posMatrix);
	vsOut.pos = mul(vsOut.pos, viewProjMatrix);

	vsOut.tex0 = vertex.tex0;

	return vsOut;
}