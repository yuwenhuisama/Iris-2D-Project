#ifndef _H_ICOLOR_
#define _H_ICOLOR_

namespace Iris2D {
	class IColor {
	public:

		virtual void SetRed(unsigned char cRed) = 0;
		virtual unsigned char GetRed() const = 0;

		virtual void SetGreen(unsigned char cGreen) = 0;
		virtual unsigned char GetGreen() const = 0;

		virtual void SetBlue(unsigned char cBlue) = 0;
		virtual unsigned char GetBlue() const = 0;

		virtual void SetAlpha(unsigned char cAlpha) = 0;
		virtual unsigned char GetAlpha() const = 0;

		virtual void Set(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) = 0;
	};
};

#endif // !_H_ICOLOR_
