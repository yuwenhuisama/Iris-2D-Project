#include "OpenGL/Iris2D/FontGL.h"

#include "Common/Util/ProxyConvert.h"
#include <functional>
#include  <codecvt>

#include <algorithm>
#include <iostream>
#include "OpenGL/Iris2D/Shaders/FontShaderGL.h"

namespace Iris2D {

	
	FT_Library FontGL::GetFTLibrary()
	{
		return m_FTLibrary;
	}

	FT_Face FontGL::GetFTFace()
	{
		return m_FTFace;
	}

	void FontGL::LoadChar(const std::wstring & wstrText)
	{
		m_nTextureMapHeight = 0;
		Characters.clear();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (const auto& c : wstrText)
		{
			if (FT_Load_Char(m_FTFace, c, FT_LOAD_RENDER)) {
				continue;
			}
			if (Characters.count(c) > 0) {
				continue;
			}
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
				0
			};
			Characters.insert(std::pair<wchar_t, Character>(c, character));
			m_nTextureMapWidth += m_FTFace->glyph->bitmap.width;
			m_nTextureMapHeight = std::max(m_nTextureMapHeight, m_FTFace->glyph->bitmap.rows);
			m_nOriginY = std::max(static_cast<int>(m_nOriginY), static_cast<int>(m_FTFace->glyph->bitmap.rows - m_FTFace->glyph->bitmap_top));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int FontGL::GetTextWidth(const std::wstring & wstrText)
	{
		float fX = 0.0f;
		for (auto& c : wstrText)
		{
			const Character& ch = Characters[c];
			GLfloat fXpos = fX + ch.m_nLeft;// ch.Bearing.x;
			fX += static_cast<float>(ch.m_nAdvance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		return fX;
	}

	void FontGL::DrawString(const std::wstring & wstrText, GLfloat fWidth, GLfloat fHeight, AlignType eAlign)
	{
		GLfloat fLeft = 0;
		if (eAlign == AlignType::Right) {
			fLeft = 0 - static_cast<GLfloat>(GetTextWidth(wstrText)) + fWidth;
		}
		else if (eAlign == AlignType::Center) {
			fLeft = 0 - static_cast<GLfloat>(GetTextWidth(wstrText)) / 2 + fWidth / 2;

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
		glClearColor(0.0f, 0.0f, 1.0f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto pShaderFont = FontShaderGL::Instance();
		pShaderFont->Initialize();
		const auto c_mt4Projection = glm::ortho(0.0f, fWidth, 0.0f, fHeight);
		pShaderFont->Use();
		pShaderFont->SetProjectionMatrix(c_mt4Projection);
		pShaderFont->SetFontColor(m_pColor); //*GetProxied<FontGL*>(GetFont())->GetColor());


		fTop = fTop+ m_nTextureMapHeight-(m_nOriginY);

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
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			Characters[c].m_nTextureMapLocationX = static_cast<int>(fLeft);

			fLeft += static_cast<float>(chCharacter.m_nAdvance >> 6);
			if (fLeft > fWidth) {
				break;
			}

		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		pTextureFont->RestoreFrameBuffer();
		pTextureFont->SaveToFile(L"d:\\hehe3.png");
		
		m_pTemporaryTexture = pTextureFont;


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
			float lean = 0.5f;
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