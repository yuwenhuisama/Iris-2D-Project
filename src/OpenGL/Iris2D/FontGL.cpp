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

	void FontGL::LoadWstring(const std::wstring& wstrText) {
		if (!m_bUseCache) {
			LoadStringWithDataBind(wstrText);
		}
	}

	void FontGL::LoadStringWithDataBind(const std::wstring & wstrText)
	{

		Characters.clear();
		m_nTextureMapHeight = 0;
	//	m_nTextureMapWidth = 0;
		m_nOriginY = 0;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (const auto& c : wstrText)
		{
			if (FT_Load_Char(m_FTFace, c, FT_LOAD_MONOCHROME)) {
				continue;
			}
			if (Characters.count(c) > 0) {
				continue;
			}
			if (m_bBold) {
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
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				nTexture,
				//glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
				m_FTFace->glyph->bitmap.width,
				m_FTFace->glyph->bitmap.rows,
				//glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
				m_FTFace->glyph->bitmap_left,
				m_FTFace->glyph->bitmap_top,
				m_FTFace->glyph->advance.x,

			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
			//m_nTextureMapWidth += m_FTFace->glyph->bitmap.width;
			m_nTextureMapHeight = std::max(m_nTextureMapHeight, m_FTFace->glyph->bitmap.rows);
			m_nOriginY = std::max(static_cast<int>(m_nOriginY), static_cast<int>(m_FTFace->glyph->bitmap.rows - m_FTFace->glyph->bitmap_top));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void FontGL::LoadStringWithoutDataBind(const std::wstring & wstrText)
	{
		m_nTextureMapHeight = 0;
	//	m_nTextureMapWidth = 0;
		m_nOriginY = 0;
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
				//glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
				m_FTFace->glyph->bitmap.width,
				m_FTFace->glyph->bitmap.rows,
				//glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
				m_FTFace->glyph->bitmap_left,
				m_FTFace->glyph->bitmap_top,

				m_FTFace->glyph->advance.x,

			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
			//m_nTextureMapWidth += m_FTFace->glyph->bitmap.width;
			m_nTextureMapHeight = std::max(m_nTextureMapHeight, m_FTFace->glyph->bitmap.rows);
			m_nOriginY = std::max(static_cast<int>(m_nOriginY), static_cast<int>(m_FTFace->glyph->bitmap.rows - m_FTFace->glyph->bitmap_top));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void FontGL::LoadChar(const wchar_t & wChar)
	{
		Characters.clear();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		if (FT_Load_Char(m_FTFace, wChar, FT_LOAD_MONOCHROME)) {
			return;
		}
		if (m_bBold) {
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
			//glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
			m_FTFace->glyph->bitmap.width,
			m_FTFace->glyph->bitmap.rows,
			//glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
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
		CharacterWicaches.clear();
		m_nTextureMapHeight = 0;
		m_nTextureMapWidth = 0;
		m_nOriginY = 0;
		if (m_bUseCache) {
			LoadStringWithoutDataBind(L"µÄbga");
			Characters.clear();
		}
		
	}

	unsigned int FontGL::GetTextWidth(const std::wstring & wstrText)
	{
		float fX = 0.0f;

		if (Characters.size() == 0) {
			LoadStringWithoutDataBind(wstrText);
		}

		for (auto& c : wstrText)
		{
			const Character& ch = Characters[c];
			fX += static_cast<float>(ch.m_nAdvance >> 6);
		}
		return fX;
	}

	TextureGL * FontGL::DrawString(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign) {
		return m_bUseCache ? DrawStringWithCache(wstrText, fWidth, fHeight, eAlign) : DrawStringWithoutCache(wstrText, fWidth, fHeight, eAlign);
	}

	TextureGL * FontGL::DrawStringWithCache(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign) {
		GLfloat fPosX = 0;
		const GLfloat fStringWidth = static_cast<GLfloat>(GetTextWidth(wstrText));
		if (eAlign == AlignType::Right) {
			fPosX = 0 - fStringWidth + fWidth;
		}
		else if (eAlign == AlignType::Center) {
			fPosX = 0 - fStringWidth /2 + fWidth / 2;

		}
		else {
			fPosX = 0;
		}
		GLfloat fLeft = 0;
		GLfloat fRight = 0;
		GLfloat fTop = 0;
		GLfloat fBottom = 0;

		
		for (auto c : wstrText) {
			if (CharacterWicaches.count(c) == 0)
				DrawCasheTexture(c);			
		}
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
		pShaderBackground->Use();
		glBindVertexArray(nVAO);
		
		
		auto pTextureFrameBuffer = Iris2D::TextureGL::CreateFrameBuffer(fWidth, fHeight);
		pTextureFrameBuffer->UseTextureAsFrameBuffer();
		glViewport(0, 0, fWidth, fHeight);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto & c: wstrText) {

			fLeft = fPosX / fWidth * 2 - 1;
			fRight = (fPosX + CharacterWicaches[c].m_pTexture->GetWidth()) / fWidth * 2 - 1;
			fBottom =-1;
			fTop = CharacterWicaches[c].m_pTexture->GetHeight() / fHeight * 2 - 1;


			GLfloat arrVertices[] = {
				//position	    //texcoord
				fRight,  fTop,   1.0f, 1.0f,
				fRight,  fBottom,   1.0f, 0.0f,
				 fLeft,  fBottom,   0.0f, 0.0f,
				 fLeft,  fTop,   0.0f, 1.0f
			};



			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arrVertices), arrVertices);
			CharacterWicaches[c].m_pTexture->UseTexture();

			//	GetTexture()->UseTexture();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			fPosX += CharacterWicaches[c].m_pTexture->GetWidth();
			if (fPosX > fWidth) break;

		}

		glBindVertexArray(0);
		pTextureFrameBuffer->RestoreFrameBuffer();

		return pTextureFrameBuffer;

	}


	TextureGL * FontGL::DrawStringWithoutCache(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign) {
		//LoadCharWithDataBind(wstrText);
		GLfloat fLeft = 0;
		const GLfloat fStringWidth = static_cast<GLfloat>(GetTextWidth(wstrText));
		if (eAlign == AlignType::Right) {
			fLeft = 0 - fStringWidth + fWidth;
		}
		else if (eAlign == AlignType::Center) {
			fLeft = 0 - fStringWidth / 2 + fWidth / 2;

		}
		else {
			fLeft = 0;
		}
		GLfloat fTop = 0;

		TextureGL::Release(m_pTemporaryTexture);
		GLuint nVAO = 0;
		GLuint nVBO = 0;

		auto pTextureFont = Iris2D::TextureGL::CreateFrameBuffer(fWidth, fHeight);

		pTextureFont->UseTextureAsFrameBuffer();
		glViewport(0, 0, fWidth, fHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShaderFont = FontShaderGL::Instance();
		pShaderFont->Initialize();
		const auto c_mt4Projection = glm::ortho(0.0f, fWidth, 0.0f, fHeight);
		pShaderFont->Use();
		pShaderFont->SetProjectionMatrix(c_mt4Projection);
		pShaderFont->SetFontColor(m_pColor); //*GetProxied<FontGL*>(GetFont())->GetColor());


		fTop = fTop + m_nTextureMapHeight - (m_nOriginY);

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

		for (auto& c : wstrText)
		{
			const Character& chCharacter = Characters[c];
			const GLfloat fXPos = fLeft + chCharacter.m_nLeft;
			const GLfloat fYPos = fTop - chCharacter.m_nTop;

			const GLfloat fTmpW = chCharacter.m_nWidth;
			const GLfloat fTmpH = chCharacter.m_nHeight;

			GLfloat vertices[6][4] = {
			{ fXPos,			fYPos + fTmpH,		0.0, 1.0 },
			{ fXPos,			fYPos,				0.0, 0.0 },
			{ fXPos + fTmpW,	fYPos,				1.0, 0.0 },

			{ fXPos,			fYPos + fTmpH,		0.0, 1.0 },
			{ fXPos + fTmpW,	fYPos,				1.0, 0.0 },
			{ fXPos + fTmpW,	fYPos + fTmpH,		1.0, 1.0 }
			};

			glBindTexture(GL_TEXTURE_2D, chCharacter.m_nTextureID);
			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			fLeft += static_cast<float>(chCharacter.m_nAdvance >> 6);
			if (fLeft > fWidth) {
				break;
			}

		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		pTextureFont->RestoreFrameBuffer();
		//pTextureFont->SaveToFile(L"d:\\hehe0.png");

		//m_pTemporaryTexture = pTextureFont;


		if (nVAO) {
			glDeleteVertexArrays(1, &nVAO);
		}

		if (nVBO) {
			glDeleteBuffers(1, &nVBO);
		}
		return pTextureFont;

	}

	

	void FontGL::DrawCasheTexture(const wchar_t & wChar )
	{
		LoadChar(wChar);
		GLfloat fLeft = 0;
		GLfloat fTop =  m_nTextureMapHeight - (m_nOriginY);

	//	TextureGL::Release(m_pTemporaryTexture);
		GLuint nVAO = 0;
		GLuint nVBO = 0;

		auto pTextureFont = Iris2D::TextureGL::CreateFrameBuffer(Characters[wChar].m_nAdvance>>6, m_nTextureMapHeight+ m_nOriginY);

		pTextureFont->UseTextureAsFrameBuffer();
		glViewport(0, 0, Characters[wChar].m_nAdvance >> 6, m_nTextureMapHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShaderFont = FontShaderGL::Instance();
		pShaderFont->Initialize();
		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<GLfloat>(Characters[wChar].m_nAdvance >> 6), 0.0f, static_cast<GLfloat>(m_nTextureMapHeight));
		pShaderFont->Use();
		pShaderFont->SetProjectionMatrix(c_mt4Projection);
		pShaderFont->SetFontColor(m_pColor); //*GetProxied<FontGL*>(GetFont())->GetColor());


		

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
		GLfloat fXPos = chCharacter.m_nLeft;
		if (m_bItalic) {
			fXPos = 0-chCharacter.m_nLeft/2;
		}
		const GLfloat fYPos = fTop - chCharacter.m_nTop;

		const GLfloat fTmpW = chCharacter.m_nWidth;
		const GLfloat fTmpH = chCharacter.m_nHeight;

		GLfloat vertices[6][4] = {
			{ fXPos,			fYPos + fTmpH,		0.0, 1.0 },
			{ fXPos,			fYPos,				0.0, 0.0 },
			{ fXPos + fTmpW,	fYPos,				1.0, 0.0 },
			{ fXPos,			fYPos + fTmpH,		0.0, 1.0 },
			{ fXPos + fTmpW,	fYPos,				1.0, 0.0 },
			{ fXPos + fTmpW,	fYPos + fTmpH,		1.0, 1.0 }
		};

			glBindTexture(GL_TEXTURE_2D, chCharacter.m_nTextureID);
			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		pTextureFont->RestoreFrameBuffer();
	//	pTextureFont->SaveToFile(L"d:\\fuck.png");

		const CharacterWithcache  cc = { pTextureFont,0 };
		CharacterWicaches.insert(std::pair<wchar_t, CharacterWithcache>(wChar, cc));

		if (nVAO) {
			glDeleteVertexArrays(1, &nVAO);
		}

		if (nVBO) {
			glDeleteBuffers(1, &nVBO);
		}

	}

	
	TextureGL * FontGL::GetTemporaryTexture()
	{
		return m_pTemporaryTexture;
	}

	bool FontGL::Existed(const std::wstring & wstrFontName)
	{
		//return m_FTFace==nullptr?false:true;
		return false;
	}

	FontGL * FontGL::Create(const std::wstring & wstrFontName)
	{
		auto pNewObject = new FontGL();
		pNewObject->IncreamRefCount();
		pNewObject->m_wstrFontName = wstrFontName;
		if (FT_Init_FreeType(&pNewObject->m_FTLibrary))
			return nullptr;
		const wchar_t* pwText = &wstrFontName[0];

		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		auto strConverted = converter.to_bytes(wstrFontName);


		if (FT_New_Face(pNewObject->m_FTLibrary, strConverted.c_str(), 0, &pNewObject->m_FTFace))
			return nullptr;
		FT_Select_Charmap(pNewObject->m_FTFace, FT_ENCODING_UNICODE);
		FT_Set_Pixel_Sizes(pNewObject->m_FTFace, 0, pNewObject->m_nSize);
		
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
	}

	const std::wstring & FontGL::GetName() const
	{
		return m_wstrFontName;
	}

	void FontGL::SetSize(unsigned int nSize)
	{
		m_nSize = nSize < 0 ? GetDefaultSize() : nSize;
		FT_Set_Pixel_Sizes(m_FTFace, 0, m_nSize);
	}

	unsigned int FontGL::GetSize() const
	{
		return m_nSize;
	}

	void FontGL::SetBold(bool bBold)
	{
		m_bBold = bBold;
	}

	bool FontGL::GetBold() const
	{
		return m_bBold;
	}

	void FontGL::SetItalic(bool bItalic)
	{
		if (bItalic && !m_bItalic) {
			float lean = 0.2f;
			FT_Matrix matrix;
			matrix.xx = 0x10000L;
			matrix.xy = lean * 0x10000L;
			matrix.yx = 0;
			matrix.yy = 0x10000L;
			FT_Set_Transform(m_FTFace, &matrix, 0);
		}
		else if (!bItalic && m_bItalic) {
			float lean = 0.0f;
			FT_Matrix matrix;
			matrix.xx = 0x10000L;
			matrix.xy = 0;
			matrix.yx = 0;
			matrix.yy = 0x10000L;
			FT_Set_Transform(m_FTFace, &matrix, 0);
		}
		m_bItalic = bItalic;
	}

	bool FontGL::GetItalic() const
	{
		return m_bItalic;
	}

	void FontGL::SetShadow(bool bShadow)
	{
		m_bShadow = bShadow;
	}

	bool FontGL::GetShadow() const
	{
		return m_bShadow;
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
		return L"C:/Windows/Fonts/simhei.ttf";
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
	}

	

}