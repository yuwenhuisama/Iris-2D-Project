//
// Globals
//

matrix WorldMatrix;
matrix ProjMatrix;
int4 ToneVector;

texture Tex;


//
// Sampler
//

sampler S0 = sampler_state
{
    Texture   = (Tex);
    MinFilter = LINEAR; 
    MagFilter = LINEAR; 
    MipFilter = LINEAR;
};

struct PS_INPUT {
	float2 uv : TEXCOORD;
};

struct PS_OUTPUT {
	vector color : COLOR;
};

PS_OUTPUT ps_main(PS_INPUT input) {
	PS_OUTPUT output = (PS_OUTPUT)0;
	float4 incolor = tex2D(S0, input.uv);
	output.color = incolor;
	float grayfull = (float)(incolor.r * 255.0f * 38.0f + incolor.g * 255.0f * 75.0f + incolor.b * 255.0f * 15.0f) / 128.0f;
	output.color.r = (float)((float)ToneVector.r + incolor.r * 255.0f + (grayfull - incolor.r * 255.0f) * (float)ToneVector.a / 255.0f) / 255.0f;
	output.color.g = (float)((float)ToneVector.g + incolor.g * 255.0f + (grayfull - incolor.g * 255.0f) * (float)ToneVector.a / 255.0f) / 255.0f;
	output.color.b = (float)((float)ToneVector.b + incolor.b * 255.0f + (grayfull - incolor.b * 255.0f) * (float)ToneVector.a / 255.0f) / 255.0f;
	
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

		pixelshader		 = compile ps_2_0 ps_main();
        fvf              = XYZ | Tex1;
        Lighting         = true;
        NormalizeNormals = true;
        SpecularEnable   = true;

        //
        // Set Transformation States

        WorldTransform[0]   = (WorldMatrix);
        ProjectionTransform = (ProjMatrix);

    }

}
