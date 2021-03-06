#ifndef _H_COLOR_DX_
#define _H_COLOR_DX_

#include "Common/Iris2D//IColor.h"
#include "DirectX/Common.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Proxied.h"

#include "Common/Util/DirtyChecker.h"


namespace Iris2D
{	
	class Color;
	class ColorDX : public Proxied<Color>, public IColor, public RefCounter
	{
	private:
		DirectX::XMINT4 m_n4Color{ 0, 0, 0, 0 };
		DirtyChecker m_dcChecker;
		DirtyChecker::DirtyCheckerHandler m_hModified = 0;

	public:
		static ColorDX* Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);
		static void Release(ColorDX*& pColor);

	public:

		void SetRed(unsigned char cRed) override;
		unsigned char GetRed() const override;

		void SetGreen(unsigned char cGreen) override;
		unsigned char GetGreen() const override;

		void SetBlue(unsigned char cBlue) override;
		unsigned char GetBlue() const override;

		void SetAlpha(unsigned char cAlpha) override;
		unsigned char GetAlpha() const override;

		void Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) override;

		bool Modified();
		void ModifyDone();

	private:
		ColorDX();
		~ColorDX() = default;
	};

	typedef ColorDX ToneDX;
}
#endif // !_H_COLOR_DX_
