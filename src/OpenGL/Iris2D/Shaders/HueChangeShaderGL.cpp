#include "OpenGL/Iris2D/Shaders/HueChangeShaderGL.h"
namespace Iris2D {

	HueChangeShaderGL * HueChangeShaderGL::Instance() {
		static HueChangeShaderGL shader;
		return &shader;
	}

	bool HueChangeShaderGL::Initialize()
	{
		return ShaderGL::Initialize("shaders/GLSL/hue_change_shader.vert", "shaders/GLSL/hue_change_shader.frag");
	}

	void HueChangeShaderGL::SetHue(int nHue)
	{
		SetInt("hsv_h", nHue);
	}

	GLuint HueChangeShaderGL::BindBufferData() {
		float arrs[] = {
			//destPoint			//Ttexcood	
			 1.0f,	 1.0f,		1.0f,1.0f,
			 1.0f,	-1.0f,   	1.0f,0.0f,
			-1.0f ,	-1.0f,		0.0f,0.0f,
			-1.0f ,	 1.0f,    	0.0f,1.0f
		};
		unsigned int arrIndiecs[] = {
			0, 1, 3,
			1, 2, 3,
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(arrs), arrs, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndiecs), arrIndiecs, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

		return VAO;
	
	}


}