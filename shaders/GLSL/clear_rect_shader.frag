#version 330 core
in vec2 TexCoord;
in vec4 Position;
in mat4 orthoMat;

out vec4 color;

uniform sampler2D ourTexture;

uniform vec4 fillLocation;

void main()
{
	vec4 fillRectxy=orthoMat*vec4(fillLocation.xy, 0.0f, 1.f);
	vec4 fillRectzw=orthoMat*vec4(fillLocation.zw, 0.0f, 1.f);

	if( Position.x>fillRectxy.x && Position.x<fillRectzw.x && Position.y>fillRectxy.y && Position.y<fillRectzw.y  ){
		color = vec4(0.0f,0.0f,0.0f,0.0f);
	}		
	else
		color = texture(ourTexture, TexCoord);


}