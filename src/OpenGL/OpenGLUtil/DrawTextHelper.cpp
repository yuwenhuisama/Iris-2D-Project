#include "OpenGL/OpenGLUtil/DrawTextHelper.h"
#include <iostream>

namespace Iris2D {
	void DrawTexHelper::LoadChar(FT_Face face, const std::wstring &text)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (auto c : text)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				continue;
			}
			if (Characters.count(c) > 0) { continue; }


			/*
			std::cout << "瞎几把搞吧+++++++++++++++++\n";
			//加粗
			FT_Pos xBold = 32;
			FT_Pos yBold = 32;
			if (1)
			{
			if (!face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
			{
			FT_BBox oldBox;
			FT_Outline_Get_CBox(&face->glyph->outline, &oldBox);
			FT_Outline_Embolden(&face->glyph->outline, xBold);

			FT_BBox newBox;
			FT_Outline_Get_CBox(&face->glyph->outline, &newBox);
			xBold = (newBox.xMax - newBox.xMin) - (oldBox.xMax - oldBox.xMin);
			yBold = (newBox.yMax - newBox.yMin) - (oldBox.yMax - oldBox.yMin);
			}
			else if (face->glyph->format == FT_GLYPH_FORMAT_BITMAP)
			{
			// FT_Library ftLibrary = FTFaceMgr::GetInstance()->GetFTLibrary();
			// FT_Bitmap_Embolden(ftLibrary, &face->glyph->bitmap, xBold, yBold);
			}
			}
			*/




			//FT_Outline_Embolden(&face->glyph->outline, 1 << 6);
			//FT_Render_Mode renderMode = (m_bAliasing ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO);

			//FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);


			//if(Characters.find(c)=)
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			// Now store character for later use
			Character character = {
				texture,
				//glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				//glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->bitmap_left,
				face->glyph->bitmap_top,

				face->glyph->advance.x
			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	unsigned int DrawTexHelper::GetTextSize(const std::wstring & wstrText) {
		float fx = 0.0f;
		for (auto c : wstrText)
		{
			Character ch = Characters[c];
			GLfloat xpos = fx + ch.nLeft;// ch.Bearing.x;
			fx += static_cast<float>(ch.Advance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		return fx;
	}

	void DrawTexHelper::Draw(const std::wstring text, GLfloat fx, GLfloat fy, GLfloat fw, GLfloat fh)
	{

		//glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);
		for (auto c : text)
		{
			Character ch = Characters[c];

			GLfloat xpos = fx + ch.nLeft;// ch.Bearing.x;
			GLfloat ypos = fy - (ch.nHeight - ch.nTop);//(ch.Size.y - ch.Bearing.y) ;

			GLfloat w = ch.nWidth;//.Size.x ;
			GLfloat h = ch.nHeight;//Size.y ;
								   //if(xpos+w>fw)
								   // Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			fx += static_cast<float>(ch.Advance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			if (fx > fw)break;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	char * DrawTexHelper::ws2c(const wchar_t * pwText)
	{
		if (!pwText)
		{
			return NULL;
		}
		size_t size = wcslen(pwText) * sizeof(wchar_t);
		char *pText = NULL;
		if (!(pText = (char*)malloc(size)))
		{
			return NULL;
		}
		size_t destlen = wcstombs(pText, pwText, size);
		/*转换不为空时，返回值为-1。如果为空，返回值0*/
		if (destlen == (size_t)(0))
		{
			return NULL;
		}

		//delete &val;
		return pText;
	}

	DrawTexHelper::DrawTexHelper() {}
	DrawTexHelper::~DrawTexHelper() {}
}