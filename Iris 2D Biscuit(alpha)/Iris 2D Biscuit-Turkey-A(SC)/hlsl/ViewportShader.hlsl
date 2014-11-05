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
	int grayfull = (output.color.r * 38 + output.color.g * 75 + output.color.b * 15) / 128;
	output.color.r = (float)(ToneVector.r + output.color.r * 255 + (grayfull - output.color.r * 255) * ToneVector.a / 255) / 255.0f;
	output.color.g = (float)(ToneVector.g + output.color.g * 255 + (grayfull - output.color.g * 255) * ToneVector.a / 255) / 255.0f;
	output.color.b = (float)(ToneVector.b + output.color.b * 255 + (grayfull - output.color.b * 255) * ToneVector.a / 255) / 255.0f;
	
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
