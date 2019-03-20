#ifndef _H_CHARACTER_GL_
#define _H_CHARACTER_GL_
#include <GL/glew.h>
#include<OpenGL/OpenGLUtil/TextureGL.h>
namespace Iris2D {
	enum class FontStyle {
		m_nBold   = 0x1,
		m_nItalic = 0x2,
		m_nShadow = 0x4,
	};

	struct Character {

		GLuint m_nTextureID;
		unsigned int m_nWidth;
		unsigned int m_nHeight;
		int m_nLeft;
		int m_nTop;
		signed long m_nAdvance;
	};
	struct CharacterWithcache {
	
		TextureGL * m_pTexture;
		int m_nTimes;
	};

	struct CharCacheMapKey {
		wchar_t m_wChar;
		unsigned int m_nSize;
		unsigned int m_nFontStyle;
		unsigned char m_ColorRed;
		unsigned char m_ColorGreen;
		unsigned char m_ColorBlue;
		unsigned char m_ColorAlpha;
	};

	struct CharCacheMapHashFunc
	{
		std::size_t operator()(const CharCacheMapKey &key) const
		{
			using std::size_t;
			using std::hash;

			return ((hash<wchar_t>()(key.m_wChar))
				^ (hash<unsigned int>()(key.m_nSize) << 1) >> 1)
				^ (hash<unsigned int>()(key.m_nFontStyle) << 1)
				^ (hash<unsigned char>()(key.m_ColorRed) << 1)
				^ (hash<unsigned char>()(key.m_ColorGreen) << 1)
				^ (hash<unsigned char>()(key.m_ColorBlue) << 1)
				^ (hash<unsigned char>()(key.m_ColorAlpha) << 1)				;
		}
	};


	struct EqualKey
	{
		bool operator () (const CharCacheMapKey &lhs, const CharCacheMapKey &rhs) const
		{
			return lhs.m_wChar == rhs.m_wChar
				&& lhs.m_nFontStyle == rhs.m_nFontStyle
				&& lhs.m_nSize == rhs.m_nSize
				&& lhs.m_ColorRed == rhs.m_ColorRed
				&& lhs.m_ColorGreen == rhs.m_ColorGreen
				&& lhs.m_ColorBlue == rhs.m_ColorBlue
				&& lhs.m_ColorAlpha == rhs.m_ColorAlpha;
		}
	};








}
#endif // _H_CHARACTER_GL_
