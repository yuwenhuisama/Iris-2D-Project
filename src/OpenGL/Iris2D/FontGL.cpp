#include "OpenGL/Iris2D/FontGL.h"

#include "Common/Util/ProxyConvert.h"
#include <functional>
#include  <codecvt>

#include <algorithm>
#include <iostream>
#include "OpenGL/Iris2D/Shaders/FontShaderGL.h"
#include "OpenGL/Iris2D/Shaders/BackGroundShaderGL.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"


#include <freetype/ftoutln.h>
#include FT_BITMAP_H

namespace Iris2D {

	
	FT_Library FontGL::GetFTLibrary()
	{
		return m_FTLibrary;
	}

	FT_Face FontGL::GetFTFace()
	{
		return m_FTFace;
	}

	void FontGL::ResetOriginAndHeight()
	{
		m_nTextureMapHeight = 0;
		m_nOriginY = 0;
		for (const auto& c : L"abgµÄ")
		{
			if (FT_Load_Char(m_FTFace, c, FT_LOAD_RENDER)) {
				continue;
			}
			m_nTextureMapHeight = std::max(m_nTextureMapHeight, m_FTFace->glyph->bitmap.rows);
			m_nOriginY = std::max(static_cast<int>(m_nOriginY), static_cast<int>(m_FTFace->glyph->bitmap.rows - m_FTFace->glyph->bitmap_top));
		}
	}

	void FontGL::LoadStringWithDataBind(const std::wstring & wstrText)
	{

		Characters.clear();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (const auto& c : wstrText)
		{
			if (FT_Load_Char(m_FTFace, c, FT_LOAD_MONOCHROME)) {
				continue;
			}
			if (Characters.count(c) > 0) {
				continue;
			}
			if (GetBold()) {
				FT_Outline_Embolden(&m_FTFace->glyph->outline, 128);
			}
			FT_Render_Glyph(m_FTFace->glyph, FT_RENDER_MODE_NORMAL);

			GLuint nTexture;
			glGenTextures(1, &nTexture);
			glBindTexture(GL_TEXTURE_2D, nTexture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				m_FTFace->glyph->bitmap.width,
				m_FTFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				m_FTFace->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				nTexture,
				m_FTFace->glyph->bitmap.width,
				m_FTFace->glyph->bitmap.rows,
				m_FTFace->glyph->bitmap_left,
				m_FTFace->glyph->bitmap_top,
				m_FTFace->glyph->advance.x,

			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void FontGL::LoadStringWithoutDataBind(const std::wstring & wstrText)
	{
		Characters.clear();
		for (const auto& c : wstrText)
		{
			if (FT_Load_Char(m_FTFace, c, FT_LOAD_RENDER)) {
				continue;
			}
			if (Characters.count(c) > 0) {
				continue;
			}
			Character character = {
				0,
				m_FTFace->glyph->bitmap.width,
				m_FTFace->glyph->bitmap.rows,
				m_FTFace->glyph->bitmap_left,
				m_FTFace->glyph->bitmap_top,
				m_FTFace->glyph->advance.x,

			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
		}
	}

	void FontGL::LoadChar(const wchar_t & wChar)
	{
		Characters.clear();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		if (FT_Load_Char(m_FTFace, wChar, FT_LOAD_MONOCHROME)) {
			return;
		}
		if (GetBold()) {
			FT_Outline_Embolden(&m_FTFace->glyph->outline, 128);
		}
		FT_Render_Glyph(m_FTFace->glyph, FT_RENDER_MODE_NORMAL);

		GLuint nTexture;
		glGenTextures(1, &nTexture);
		glBindTexture(GL_TEXTURE_2D, nTexture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			m_FTFace->glyph->bitmap.width,
			m_FTFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_FTFace->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			nTexture,
			m_FTFace->glyph->bitmap.width,
			m_FTFace->glyph->bitmap.rows,
			m_FTFace->glyph->bitmap_left,
			m_FTFace->glyph->bitmap_top,
			m_FTFace->glyph->advance.x,

		};
		Characters.insert(std::pair<wchar_t, Character>(wChar, character));
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void FontGL::SetUseCache(bool bUseCach)
	{
		m_bUseCache = bUseCach;
		Characters.clear();
		ResetOriginAndHeight();	
		if (!bUseCach) {
			CharacterWicaches.clear();
		}
	}

	unsigned int FontGL::GetTextWidth(const std::wstring & wstrText)
	{
		float fX = 0.0f;
		LoadStringWithoutDataBind(wstrText);
		for (auto& c : wstrText)
		{
			fX += static_cast<float>(Characters[c].m_nAdvance >> 6);
		}
		Characters.clear();
		return fX;
	}

	TextureGL * FontGL::DrawString(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign) {
		if (m_bUseCache) {
			m_nDrawTimes++;
		}
		if (m_bUseCache && m_nDrawTimes % 800 == 0 && CharacterWicaches.size()>0) {
			for (auto & c: CharacterWicaches) {
				if (c.second.m_nTimes < 3) {
					TextureGL::Release(c.second.m_pTexture);
					CharacterWicaches.erase(c.first);
				}
				c.second.m_nTimes /= 2;
			}
		}
		return m_bUseCache ? DrawStringWithCache(wstrText, fWidth, fHeight, eAlign) : DrawStringWithoutCache(wstrText, fWidth, fHeight, eAlign);
	}
	
	GLfloat  FontGL::GetAlignLeft(GLfloat fRectWidth, GLfloat fStringWidth, AlignType eAlign) {
		
		if (eAlign == AlignType::Right) {
			return 0 - fStringWidth + fRectWidth;
		}
		else if (eAlign == AlignType::Center) {
			return 0 - fStringWidth / 2 + fRectWidth / 2;
		}
		else {
			return 0;
		}
	
	}

	TextureGL * FontGL::DrawStringWithCache(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign) {
		for (auto & c : wstrText) {
			const CharCacheMapKey &ccKey = { c,m_nSize,m_nFontStyle,m_pColor->GetRed(),m_pColor->GetGreen(),m_pColor->GetBlue(),m_pColor->GetAlpha() };
			if (CharacterWicaches.count(ccKey) == 0) {
				DrawCasheTexture(c);
			}
		}

		const GLfloat fStringWidth = static_cast<GLfloat>(GetTextWidth(wstrText));
		GLfloat fPosX = GetAlignLeft(fWidth, fStringWidth, eAlign);
		GLfloat fLeft = 0;
		GLfloat fRight = 0;
		GLfloat fTop = 0;
		GLfloat fBottom = 0;

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;

		if (!OpenGLHelper::Instance()->CreateVertextBuffer(nullptr, 4 * 4 * sizeof(GLfloat), nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		})) {
			return nullptr;
		}
		auto pShaderBackground = BackGroundShaderGL::Instance();
		//pShaderBackground->Initialize();
		pShaderBackground->Use();
		glBindVertexArray(nVAO);

		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(fWidth, fHeight);
		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, fWidth, fHeight);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto & c : wstrText) {
			const CharCacheMapKey &ccKey = { c,m_nSize,m_nFontStyle,m_pColor->GetRed(),m_pColor->GetGreen(),m_pColor->GetBlue(),m_pColor->GetAlpha() };
			fLeft = fPosX / fWidth * 2 - 1;
			fRight = (fPosX + CharacterWicaches[ccKey].m_pTexture->GetWidth()) / fWidth * 2 - 1;
			fBottom = -1;
			fTop = CharacterWicaches[ccKey].m_pTexture->GetHeight() / fHeight * 2 - 1;
			GLfloat arrVertices[] = {
				//position	    //texcoord
				fRight,  fTop,		1.0f, 1.0f,
				fRight,  fBottom,   1.0f, 0.0f,
				fLeft,	 fBottom,	0.0f, 0.0f,
				fLeft,   fTop,		0.0f, 1.0f
			};
			CharacterWicaches[ccKey].m_pTexture->UseTexture();
			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arrVertices), arrVertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			CharacterWicaches[ccKey].m_nTimes++;
			fPosX += CharacterWicaches[ccKey].m_pTexture->GetWidth();
			if (fPosX > fWidth) break;
			//break;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		pTextureFrameBuffer->RestoreFrameBuffer();
		return pTextureFrameBuffer;
	}

	TextureGL * FontGL::DrawStringWithoutCache(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign) {
		LoadStringWithDataBind(wstrText);
		GLfloat fStringWidth = 0;
		for (auto& c : wstrText){
			fStringWidth += static_cast<float>(Characters[c].m_nAdvance >> 6);
		}
		GLfloat fLeft = GetAlignLeft(fWidth, fStringWidth, eAlign);	
		GLfloat fTop = 0;
		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;
		auto pTextureFont = Iris2D::TextureGL::CreateFrameBuffer(fWidth, fHeight);
		pTextureFont->UseTextureAsFrameBuffer();
		glViewport(0, 0, fWidth, fHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShaderFont = FontShaderGL::Instance();
		const auto c_mt4Projection = glm::ortho(0.0f, fWidth, 0.0f, fHeight);
		pShaderFont->Use();
		pShaderFont->SetProjectionMatrix(c_mt4Projection);
		auto pShadowColor = Color::Create(m_pColor->GetRed(), m_pColor->GetGreen(), m_pColor->GetBlue(), m_pColor->GetAlpha() >> 1);
		fTop = fTop + m_nTextureMapHeight - (m_nOriginY);
		if (!OpenGLHelper::Instance()->CreateVertextBuffer(nullptr, sizeof(GLfloat)*4*4, nVAO, nVBO, nEBO, [&]() -> void {
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),static_cast<void *>(0));
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		})) {
			return nullptr;
		}
		glBindVertexArray(nVAO);
		for (auto& c : wstrText)
		{
			pShaderFont->SetFontColor(m_pColor);
			const Character& chCharacter = Characters[c];
			const GLfloat & fXPos = fLeft + chCharacter.m_nLeft;
			const GLfloat &fYPos = fTop - chCharacter.m_nTop;
			const GLfloat &fTmpW = chCharacter.m_nWidth;
			const GLfloat &fTmpH = chCharacter.m_nHeight;
			for (GLfloat fShadow = 0; fShadow <=4; fShadow += 4) {
				GLfloat vertices[4][4] = {
				{ fXPos + fTmpW + fShadow,	fYPos + fTmpH + fShadow,		1.0, 1.0 },
				{ fXPos + fTmpW + fShadow,	fYPos + fShadow,				1.0, 0.0 },
				{ fXPos + fShadow,			fYPos + fShadow,				0.0, 0.0 },
				{ fXPos + fShadow,			fYPos + fTmpH + fShadow,		0.0, 1.0 }
				};
				glBindTexture(GL_TEXTURE_2D, chCharacter.m_nTextureID);
				glBindBuffer(GL_ARRAY_BUFFER, nVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				if (GetShadow()) {
					pShaderFont->SetFontColor(pShadowColor);
				}
				else {
					break;
				}
			}
			if (fLeft > fWidth) {
				break;
			}
			fLeft += static_cast<float>(chCharacter.m_nAdvance >> 6);
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		pTextureFont->RestoreFrameBuffer();
		Color::Release(pShadowColor);
		if (nVAO) {
			glDeleteVertexArrays(1, &nVAO);
		}
		if (nVBO) {
			glDeleteBuffers(1, &nVBO);
		}
		if (nEBO) {
			glDeleteBuffers(1, &nEBO);
		}
		return pTextureFont;
	}

	void FontGL::DrawCasheTexture(const wchar_t & wChar )
	{
		LoadChar(wChar);
		GLfloat fLeft = 0;
		GLfloat fTop =  m_nTextureMapHeight - (m_nOriginY);
		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLfloat fShadow = 0;
		auto pShadowColor = Color::Create(m_pColor->GetRed(), m_pColor->GetGreen(), m_pColor->GetBlue(), m_pColor->GetAlpha()>>1);
		if (GetShadow()) {
			fShadow = 4;
		}		
		auto pTextureFont = Iris2D::TextureGL::CreateFrameBuffer((Characters[wChar].m_nAdvance>>6), m_nTextureMapHeight );
		pTextureFont->UseTextureAsFrameBuffer();
		glViewport(0, 0, (Characters[wChar].m_nAdvance >> 6 ), m_nTextureMapHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShaderFont = FontShaderGL::Instance();
		pShaderFont->Initialize();
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<GLfloat>(Characters[wChar].m_nAdvance >> 6), 0.0f, static_cast<GLfloat>(m_nTextureMapHeight));
		pShaderFont->Use();
		pShaderFont->SetProjectionMatrix(c_mt4Projection);
		if (GetShadow()) {
			pShaderFont->SetFontColor(pShadowColor);
		}
		else {
			pShaderFont->SetFontColor(m_pColor);
		}

		glGenVertexArrays(1, &nVAO);
		glGenBuffers(1, &nVBO);
		glBindVertexArray(nVAO);
		glBindBuffer(GL_ARRAY_BUFFER, nVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(nVAO);
		const Character& chCharacter = Characters[wChar];
		for (; fShadow >= 0; fShadow -= 4) {
			GLfloat fXPos = chCharacter.m_nLeft;
			if (m_nFontStyle & static_cast<unsigned int>(FontStyle::m_nItalic) > 0) {
				fXPos = 0 - chCharacter.m_nLeft / 2;
			}
			const GLfloat fYPos = fTop - chCharacter.m_nTop;

			const GLfloat fTmpW = chCharacter.m_nWidth;
			const GLfloat fTmpH = chCharacter.m_nHeight;

			GLfloat vertices[6][4] = {
				{ fXPos + fShadow,			fYPos + fTmpH + fShadow,		0.0, 1.0 },
				{ fXPos + fShadow,			fYPos + fShadow,				0.0, 0.0 },
				{ fXPos + fTmpW + fShadow,	fYPos + fShadow,				1.0, 0.0 },
				{ fXPos + fShadow,			fYPos + fTmpH + fShadow,		0.0, 1.0 },
				{ fXPos + fTmpW + fShadow,	fYPos + fShadow,				1.0, 0.0 },
				{ fXPos + fTmpW + fShadow,	fYPos + fTmpH + fShadow,		1.0, 1.0 }
			};

			glBindTexture(GL_TEXTURE_2D, chCharacter.m_nTextureID);
			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			if (GetShadow()) {
				pShaderFont->SetFontColor(m_pColor);
			}
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		Color::Release(pShadowColor);
		pTextureFont->RestoreFrameBuffer();
		//pTextureFont->SaveToFile(L"d:\\fuck.png");
		const CharacterWithcache &ccValue = { pTextureFont,0};
		const CharCacheMapKey &ckKey = { wChar,m_nSize,m_nFontStyle,m_pColor->GetRed(),m_pColor->GetGreen(),m_pColor->GetBlue(),m_pColor->GetAlpha() };
		CharacterWicaches.insert(std::pair<CharCacheMapKey, CharacterWithcache>(ckKey, ccValue));
		if (nVAO) {
			glDeleteVertexArrays(1, &nVAO);
		}
		if (nVBO) {
			glDeleteBuffers(1, &nVBO);
		}
	}

	bool FontGL::Existed(const std::wstring & wstrFontName)
	{
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		auto strConverted = converter.to_bytes(wstrFontName);
		if (FILE *file = fopen(strConverted.c_str(), "r")) {
			fclose(file);
			return true;
		}
		else {
			return false;
		}

	}

	FontGL * FontGL::Create(const std::wstring & wstrFontName)
	{
		auto pNewObject = new FontGL();
		pNewObject->IncreamRefCount();
		pNewObject->m_wstrFontName = wstrFontName;
		if (FT_Init_FreeType(&pNewObject->m_FTLibrary))
			return nullptr;

		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		auto strConverted = converter.to_bytes(wstrFontName);


		if (FT_New_Face(pNewObject->m_FTLibrary, strConverted.c_str(), 0, &pNewObject->m_FTFace))
			return nullptr;
		FT_Select_Charmap(pNewObject->m_FTFace, FT_ENCODING_UNICODE);
		FT_Set_Pixel_Sizes(pNewObject->m_FTFace, 0, pNewObject->m_nSize);
		
		pNewObject->ResetOriginAndHeight();
		return pNewObject;

	}

	void FontGL::Release(FontGL *& pFont)
	{
		if (!pFont) {
			return;
		}

		pFont->DecreamRefCount();
		if (pFont->GetRefCount() == 0) {
			delete pFont;
			pFont = nullptr;
		}
	}

	void FontGL::SetName(const std::wstring & wstrFontName)
	{
		m_wstrFontName = wstrFontName;
		FT_Done_Face(m_FTFace);
		FT_Done_FreeType(m_FTLibrary);
		if (CharacterWicaches.size()>0) {
			for (auto & c : CharacterWicaches) {
				TextureGL::Release(c.second.m_pTexture);
				CharacterWicaches.erase(c.first);
			}
		}
		if (!FT_Init_FreeType(&m_FTLibrary)) {
			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;
			auto strConverted = converter.to_bytes(wstrFontName);
			if (FT_New_Face(m_FTLibrary, strConverted.c_str(), 0, &m_FTFace)) {
				FT_Select_Charmap(m_FTFace, FT_ENCODING_UNICODE);
				FT_Set_Pixel_Sizes(m_FTFace, 0, m_nSize);
				ResetOriginAndHeight();
			}
		}

	}

	const std::wstring & FontGL::GetName() const
	{
		return m_wstrFontName;
	}

	void FontGL::SetSize(unsigned int nSize)
	{
		m_nSize = nSize < 0 ? GetDefaultSize() : nSize;
		FT_Set_Pixel_Sizes(m_FTFace, 0, m_nSize);
		ResetOriginAndHeight();
	}

	unsigned int FontGL::GetSize() const
	{
		return m_nSize;
	}

	void FontGL::SetBold(bool bBold)
	{
		if (bBold) {
			m_nFontStyle = static_cast<unsigned int>(FontStyle::m_nBold) | m_nFontStyle;
		}
		else {
			m_nFontStyle= (~static_cast<unsigned int>(FontStyle::m_nBold)) & m_nFontStyle;
		}

		
	}

	bool FontGL::GetBold() const
	{
		//return m_nFontStyle>= static_cast<unsigned int>(FontStyle::m_nBold);
		return m_nFontStyle & static_cast<unsigned int>(FontStyle::m_nBold);
	}

	void FontGL::SetItalic(bool bItalic)
	{
		if (bItalic) {
			float fLean = 0.2f;
			static FT_Matrix matrix;
			matrix.xx = 0x10000L;
			matrix.xy = fLean * 0x10000L;
			matrix.yx = 0;
			matrix.yy = 0x10000L;
			FT_Set_Transform(m_FTFace, &matrix, 0);
			m_nFontStyle = static_cast<unsigned int>(FontStyle::m_nItalic) | m_nFontStyle;
		}
		else {
			static FT_Matrix matrix;
			matrix.xx = 0x10000L;
			matrix.xy = 0;
			matrix.yx = 0;
			matrix.yy = 0x10000L;
			FT_Set_Transform(m_FTFace, &matrix, 0);
			m_nFontStyle = (~static_cast<unsigned int>(FontStyle::m_nItalic)) & m_nFontStyle;
		}
		
	}

	bool FontGL::GetItalic() const
	{
		//return  m_nFontStyle >= static_cast<unsigned int>(FontStyle::m_nItalic);
		return  m_nFontStyle & static_cast<unsigned int>(FontStyle::m_nItalic);
	}

	void FontGL::SetShadow(bool bShadow)
	{
		if (bShadow) {
			m_nFontStyle = static_cast<unsigned int>(FontStyle::m_nShadow) | m_nFontStyle;
		}
		else {
			m_nFontStyle = (~static_cast<unsigned int>(FontStyle::m_nShadow)) & m_nFontStyle;
		}
	}

	bool FontGL::GetShadow() const
	{
		return  m_nFontStyle & static_cast<unsigned int>(FontStyle::m_nShadow);
	}

	void FontGL::SetColor(Color *& pColor)
	{
		m_pColor = pColor;
	}

	Color * FontGL::GetColor() const
	{
		return m_pColor?GetDefaultColor(): m_pColor;
	}

	std::wstring FontGL::GetDefaultName()
	{
		return L"fonts/simhei.ttf";
	}

	unsigned int FontGL::GetDefaultSize()
	{
		return 20;
	}

	bool FontGL::GetDefaultBold()
	{
		return false;
	}

	bool FontGL::GetDefaultItalic()
	{
		return false;
	}

	bool FontGL::GetDefaultShadow()
	{
		return false;
	}

	Color * FontGL::GetDefaultColor()
	{
		static Color* pDefaultColor = Color::Create(0, 0, 0, 255);
		return pDefaultColor;
	}

	FontGL::FontGL() : RefCounter() {
	
	}

	FontGL::~FontGL(){
		FT_Done_Face(m_FTFace);
		FT_Done_FreeType(m_FTLibrary);

		if ( CharacterWicaches.size()>0) {
			for (auto & c : CharacterWicaches) {
				TextureGL::Release(c.second.m_pTexture);
				CharacterWicaches.erase(c.first);
			}
		}

	}

	

}