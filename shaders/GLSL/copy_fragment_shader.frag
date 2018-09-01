#version 330 core
in vec2 DesTexCoord;
in mat4 DesOthoMat;
in vec4 Position;

out vec4 color;

uniform sampler2D desTexture;
uniform sampler2D srcTexture;
uniform float opacity;
uniform vec4 desRect;
uniform vec4 srcRect;

void main()
{
	vec4 desRectxy=DesOthoMat*vec4(desRect.xy, 0.0f, 1.f);
	vec4 desRectzw=DesOthoMat*vec4(desRect.zw, 0.0f, 1.f);

	if( Position.x>desRectxy.x && Position.x<desRectzw.x && Position.y>desRectxy.y && Position.y<desRectzw.y  ){
	    vec2 src=vec2(   
						srcRect.x+  (Position.x-desRectxy.x)/((desRectzw.x-desRectxy.x))*  (srcRect.z-srcRect.x),
					    (1-srcRect.y)+ ((Position.y-desRectxy.y)/((desRectxy.y-desRectzw.y)))*  (srcRect.w-srcRect.y)
					);
		color = mix(texture(desTexture, DesTexCoord), texture(srcTexture, src), opacity);
	}
	else{
		color=texture(desTexture, DesTexCoord);
	}
}