#ifndef _H_COLOR_DX_
#define _H_COLOR_DX_

#include "Common/Iris2D//IColor.h"
#include "DirectX/Common.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Proxied.h"


namespace Iris2D
{	
	class Color;
	class ColorDX : public Proxied<Color>, public IColor, public RefCounter
	{
	private:
		DirectX::XMINT4 m_n4Color{ 0, 0, 0, 0 };
		bool m_bModifyDirtyFlag = false;

	public:
		static ColorDX* Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);
		static void Release(ColorDX*& pColor);

	public:


		void SetRed(unsigned char cRed);
		unsigned char GetRed() const;

		void SetGreen(unsigned char cGreen);
		unsigned char GetGreen() const;

		void SetBlue(unsigned char cBlue);
		unsigned char GetBlue() const;

		void SetAlpha(unsigned char cAlpha);
		unsigned char GetAlpha() const;

		void Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);

		bool Modified();
		void ModifyDone();

	private:
		ColorDX() = default;
		~ColorDX() = default;
	};

	typedef ColorDX ToneDX;
}
#endif // !_H_COLOR_DX_
