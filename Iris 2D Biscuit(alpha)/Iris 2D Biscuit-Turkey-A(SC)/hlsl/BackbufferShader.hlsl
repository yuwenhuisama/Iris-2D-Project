//
// Globals
//

matrix WorldMatrix;
matrix ProjMatrix;

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

		pixelshader  = compile ps_2_0 ps_main();
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
