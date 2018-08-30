#include "OpenGL/OpenGLUtil/DrawTextHelper.h"
#include <iostream>

namespace Iris2D {
	void DrawTexHelper::LoadChar(FT_Face ftFace, const std::wstring &wstrText)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (const auto& c : wstrText)
		{
			if (FT_Load_Char(ftFace, c, FT_LOAD_RENDER)) {
				continue;
			}

			if (Characters.count(c) > 0) {
				continue;
			}

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				ftFace->glyph->bitmap.width,
				ftFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				ftFace->glyph->bitmap.buffer
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
				//glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
				ftFace->glyph->bitmap.width,
				ftFace->glyph->bitmap.rows,
				//glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
				ftFace->glyph->bitmap_left,
				ftFace->glyph->bitmap_top,

				ftFace->glyph->advance.x
			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenVertexArrays(1, &m_nVAO);
		glGenBuffers(1, &m_nVBO);
		glBindVertexArray(m_nVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_nVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	unsigned int DrawTexHelper::GetTextSize(const std::wstring & wstrText) {
		float fX = 0.0f;
		for (auto& c : wstrText)
		{
			const Character& ch = Characters[c];
			GLfloat fXpos = fX + ch.m_nLeft;// ch.Bearing.x;
			fX += static_cast<float>(ch.m_nAdvance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		return fX;
	}

	void DrawTexHelper::Draw(const std::wstring& wstrText, GLfloat fX, GLfloat fY, GLfloat fW, GLfloat fH)
	{

		//glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_nVAO);
		for (auto& c : wstrText)
		{
			const Character& chCharacter = Characters[c];

			const GLfloat fXPos = fX + chCharacter.m_nLeft;// ch.Bearing.x;
			const GLfloat fYPos = fY - (chCharacter.m_nHeight - chCharacter.m_nTop);//(ch.Size.y - ch.Bearing.y) ;

			const GLfloat fTmpW = chCharacter.m_nWidth;//.Size.x ;
			const GLfloat fTmpH = chCharacter.m_nHeight;//Size.y ;

			GLfloat vertices[6][4] = {
			{ fXPos,     fYPos + fTmpH,   0.0, 0.0 },
			{ fXPos,     fYPos,       0.0, 1.0 },
			{ fXPos + fTmpW, fYPos,       1.0, 1.0 },

			{ fXPos,     fYPos + fTmpH,   0.0, 0.0 },
			{ fXPos + fTmpW, fYPos,       1.0, 1.0 },
			{ fXPos + fTmpW, fYPos + fTmpH,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, chCharacter.m_nTextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, m_nVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			fX += static_cast<float>(chCharacter.m_nAdvance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

			if (fX > fW) {
				break;
			}
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	DrawTexHelper::~DrawTexHelper() {
		if (m_nVAO) {
			glDeleteVertexArrays(1, &m_nVAO);
		}

		if (m_nVBO) {
			glDeleteBuffers(1, &m_nVBO);
		}
	}
}