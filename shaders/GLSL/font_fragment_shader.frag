#version 330 core

in vec2 TexCoords;
in vec4 Position;;

out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

uniform vec4 desRect;

void main()
{    

		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
		color = textColor* sampled;

}  