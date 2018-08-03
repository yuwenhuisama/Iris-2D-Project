#ifndef _H_RECT_GL_
#define _H_RECT_GL_

#include "OpenGL/Common.h"
#include "Common/Iris2D/IRect.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Proxied.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Iris2D
{
	class Rect;
	class RectGL : public Proxied<Rect>, public IRect, public RefCounter
	{
	private:
		glm::vec4 m_f4Rect{ 0.0f, 0.0f, 0.0f, 0.0f };


		bool m_bModifyDirtyFlag = false;

	public:
		static RectGL* Create(float fX, float fY, float fWidth, float fHeight);

		static RectGL* Create2(float fLeft, float fTop, float fRight, float fBottom);

		static void Release(RectGL*& pRect);

	public:
		
		void SetX(float fX);
		
		float GetX() const;

		void SetY(float fY);
		
		float GetY() const;

		void SetWidth(float fWidth);
	
		float GetWidth() const;

		void SetHeight(float fHeight);
	
		float GetHeight() const;

		
		void SetLeft(float fLeft);
	
		float GetLeft() const;

		void SetTop(float fTop);
	
		float GetTop() const;

		void SetRight(float fRight);
	
		float GetRight() const;

		void SetBottom(float fBottom);
	
		float GetBottom() const;

		void Set(float fX, float fY, float fWidth, float fHeight);
	
		void Set2(float fLeft, float fTop, float fRight, float fBottom);

		bool Modified();
		void ModifyDone();

	private:
		RectGL() = default;
		~RectGL() = default;
	};
}
#endif // !_H_RECT_GL_