#ifndef _H_COLOR_GL_
#define _H_COLOR_GL_

#include "Common/Iris2D//IColor.h"
#include "OpenGL/Common.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Proxied.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common/Util/DirtyChecker.h"

namespace Iris2D
{

	class Color;
	class ColorGL : public Proxied<Color>, public IColor, public RefCounter
	{
	private:
		glm::ivec4 m_n4Color{ 0, 0, 0, 0 };
		DirtyChecker m_dcChecker;
		DirtyChecker::DirtyCheckerHandler m_hModified = 0;

	public:
		static ColorGL* Create(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha);
		static void Release(ColorGL*& pColor);

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
		ColorGL();
		~ColorGL() = default;
	};

	typedef ColorGL ToneDX;
}
#endif // !_H_COLOR_GL_
