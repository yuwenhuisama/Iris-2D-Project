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

// 
// Effect
//

technique LightAndTexture
{
    pass P0
    {
        //
        // Set Misc render states.

		vertexshader	 = null;
		pixelshader		 = null;
        fvf              = XYZ | Tex1;
        Lighting         = true;
        NormalizeNormals = true;
        SpecularEnable   = true;

        //
        // Set Transformation States

        WorldTransform[0]   = (WorldMatrix);
        ProjectionTransform = (ProjMatrix);

		Sampler[0] = (S0);

    }

}
