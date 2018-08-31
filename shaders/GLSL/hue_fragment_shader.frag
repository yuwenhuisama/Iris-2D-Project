#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;
uniform int hsv_h;

void main()
{
	//int hsv_h=120;
	
	color = texture(ourTexture, TexCoord);
	float fMax=0;
	if(color.x>=color.y && color.x>=color.z) fMax=color.x;
	else if(color.y>=color.x && color.y>=color.z) fMax=color.y;
	else if(color.z>=color.x && color.z>=color.y) fMax=color.z;
	
	float fMin=0;
	if(color.x<=color.y && color.x<=color.z) fMin=color.x;
	else if(color.y<=color.x && color.y<=color.z) fMin=color.y;
	else if(color.z<=color.x && color.z<=color.y) fMin=color.z;
	
	float hsv_s=0.0f;
	if(fMax!=0.0f) hsv_s=(fMax-fMin)/fMax;

	float hsv_v =fMax;
	
	int hsv_h2 =hsv_h/60;
	
	float c =hsv_v*hsv_s;
	float x=0;
	if(hsv_h2 % 2>1)	
		x=c*(1-(hsv_h2%2-1)) ;
	else
		x=c*(1+(hsv_h2%2-1)) ;

	float m=hsv_v-c;

	if(hsv_h2>=0.0f && hsv_h2<=1.0f)      color=vec4(c+m,    x,    m,    color.w);
	else if(hsv_h2>1.0f  && hsv_h2<=2.0f) color=vec4(x+m,    c,    m,    color.w);
	else if(hsv_h2>2.0f  && hsv_h2<=3.0f) color=vec4(m,      c,    x+m,    color.w);
	else if(hsv_h2>3.0f  && hsv_h2<=4.0f) color=vec4(m,      x,    c+m,    color.w);
	else if(hsv_h2>4.0f  && hsv_h2<=5.0f) color=vec4(x+m,    m,    c+m,    color.w);
	else if(hsv_h2>5.0f  && hsv_h2<=6.0f) color=vec4(c+m,    m,    x+m,    color.w);
	else  color=vec4(m,m,m, color.w);		
	 

	//if(hsv_h2>=0.0f && hsv_h2<=1.0f)      color=vec4(c,    x,    0.0f, color.w);
	//else if(hsv_h2>1.0f  && hsv_h2<=2.0f) color=vec4(x,    c,    0.0f, color.w);
	//else if(hsv_h2>2.0f  && hsv_h2<=3.0f) color=vec4(0.0f, c,    x,    color.w);
	//else if(hsv_h2>3.0f  && hsv_h2<=4.0f) color=vec4(0.0f, x,    c,    color.w);
	//else if(hsv_h2>4.0f  && hsv_h2<=5.0f) color=vec4(x,    0.0f, c,    color.w);
	//else if(hsv_h2>5.0f  && hsv_h2<=6.0f) color=vec4(c,    0.0f, x,    color.w);
	//else  color=vec4(0.0f,0.0f,0.0f, color.w);		
	 
}
