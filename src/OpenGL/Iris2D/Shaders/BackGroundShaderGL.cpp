#include "Common/Util/DebugUtil.h"
#include "OpenGL/Iris2D/Shaders/BackGroundShaderGL.h"

namespace Iris2D {
	
	BackGroundShaderGL* BackGroundShaderGL::Instance() {
		static BackGroundShaderGL fontshader;
		return &fontshader;
	}
	bool BackGroundShaderGL::Initialize()
	{
		return ShaderGL::Initialize("shaders/GLSL/backgroud_shader.vert", "shaders/GLSL/backgroud_shader.frag");

	}

	GLuint BackGroundShaderGL::BindBufferData()
	{
		GLfloat vertices[] = {
		    //position	    //texcoord
			 1.0f,  1.0f,   1.0f, 1.0f,   // 右上
			 1.0f, -1.0f,   1.0f, 0.0f,   // 右下
			-1.0f, -1.0f,   0.0f, 0.0f,   // 左下
			-1.0f,  1.0f,   0.0f, 1.0f    // 左上
		};
		GLuint indices[] = {  
			0, 1, 3, 
			1, 2, 3  
		};
		GLuint VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0); // Unbind VAO
		return VAO;
	}

}