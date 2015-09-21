//
// Globals
//

matrix WorldMatrix;
matrix ProjMatrix;
float4 ToneVector;
int Opacity;
int Duration;
int CurDuration;
int FlashVisible;
float4 SpriteXY;
float4 FlashColor;

int BlendType;

texture Tex;
texture BackgroundTex;

float4 MultiTextureSize;

//
// Sampler
//

struct VS_INPUT {
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT {
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

sampler S0 = sampler_state
{
    Texture   = (Tex);
    MinFilter = LINEAR; 
    MagFilter = LINEAR; 
    MipFilter = LINEAR;
};

sampler S1 = sampler_state
{
	Texture   = (BackgroundTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct PS_INPUT {
	float2 uv : TEXCOORD;
};

struct PS_OUTPUT {
	float4 color : COLOR;
};

VS_OUTPUT vs_main(VS_INPUT input){

	VS_OUTPUT output = input;
	output.position = mul(output.position, WorldMatrix);
	output.position.x += SpriteXY.x;
	output.position.y += SpriteXY.y;
	output.position = mul(output.position , ProjMatrix);

	return output;
}

PS_OUTPUT ps_main(PS_INPUT input) {
	PS_OUTPUT output = (PS_OUTPUT)0;
	float4 incolor = tex2D(S0, input.uv);
	float2 bguv;
	bguv.x = (SpriteXY.x + input.uv.x * MultiTextureSize.x) / MultiTextureSize.z;
	bguv.y = (SpriteXY.y + input.uv.y * MultiTextureSize.y) / MultiTextureSize.w;
	float4 bgcolor = tex2D(S1, bguv);

	output.color = incolor;
	output.color.a = incolor.a * (float)Opacity / 255.0f;

	float grayfull = (incolor.r * 255.0f * 38.0f + incolor.g * 255.0f * 75.0f + incolor.b * 255.0f * 15.0f) / 128.0f;
	output.color.r = (ToneVector.r + incolor.r * 255.0f + (grayfull - incolor.r * 255.0f) * ToneVector.a / 255.0f) / 255.0f;
	output.color.g = (ToneVector.g + incolor.g * 255.0f + (grayfull - incolor.g * 255.0f) * ToneVector.a / 255.0f) / 255.0f;
	output.color.b = (ToneVector.b + incolor.b * 255.0f + (grayfull - incolor.b * 255.0f) * ToneVector.a / 255.0f) / 255.0f;

	// -- blend --
	// Add
	if (BlendType == 1) {
		output.color.r = bgcolor.r + output.color.r;
		output.color.g = bgcolor.g + output.color.g;
		output.color.b += bgcolor.b + output.color.b;
		//output.color.a += bgcolor.a;
	}
	// Dec
	else if (BlendType == 2) {
		output.color.r = bgcolor.r - output.color.r;
		output.color.g = bgcolor.g - output.color.g;
		output.color.b = bgcolor.b - output.color.b ;
		//output.color.a -= bgcolor.a;
	}

	output.color.r = output.color.r > 1.0f ? 1.0f : (output.color.r < 0.0f ? 0.0f : output.color.r);
	output.color.g = output.color.g > 1.0f ? 1.0f : (output.color.g < 0.0f ? 0.0f : output.color.g);
	output.color.b = output.color.b > 1.0f ? 1.0f : (output.color.b < 0.0f ? 0.0f : output.color.b);
	 
	// -- flash --

	if (FlashVisible == 1) {
		output.color.r = output.color.r + (FlashColor.r - output.color.r) * (float)CurDuration / (float)Duration;
		output.color.g = output.color.g + (FlashColor.g - output.color.g) * (float)CurDuration / (float)Duration;
		output.color.b = output.color.b + (FlashColor.b - output.color.b) * (float)CurDuration / (float)Duration;
	}

	return output;
}

// 
// Effect
//

technique LightAndTexture
{
    pass P0
    {
        //
        // Set Misc render states.

		pixelshader 	 = compile ps_2_0 ps_main();
		vertexshader     = compile vs_2_0 vs_main();

//        fvf              = XYZ | Normal | Tex1;
        fvf              = XYZ | Tex1;
        Lighting         = true;
        NormalizeNormals = true;
        SpecularEnable   = false;

        //
        // Set Transformation States

        //WorldTransform[0]   = (WorldMatrix);
        //ProjectionTransform = (ProjMatrix);

    }

}
