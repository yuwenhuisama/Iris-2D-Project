#ifndef _H_RECT_GL_
#define _H_RECT_GL_

#include "OpenGL/Common.h"
#include "Common/Iris2D/IRect.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Proxied.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common/Util/DirtyChecker.h"

namespace Iris2D
{
	class Rect;
	class RectGL : public Proxied<Rect>, public IRect, public RefCounter
	{
		REF_FRIEND_DECLARE;

	private:
		glm::vec4 m_f4Rect{ 0.0f, 0.0f, 0.0f, 0.0f };

		DirtyChecker m_dcChecker;
		DirtyChecker::DirtyCheckerHandler m_hModified = 0;
		//bool m_bModifyDirtyFlag = false;

	public:
		static RectGL* Create(float fX, float fY, float fWidth, float fHeight);
		static RectGL* Create2(float fLeft, float fTop, float fRight, float fBottom);
		static void Release(RectGL*& pRect);

	public:
		
		void SetX(float fX) override;
		float GetX() const override;

		void SetY(float fY) override;
		float GetY() const override;

		void SetWidth(float fWidth) override;
		float GetWidth() const override;

		void SetHeight(float fHeight) override;
		float GetHeight() const override;
	
		void SetLeft(float fLeft) override;
		float GetLeft() const override;

		void SetTop(float fTop) override;
		float GetTop() const override;

		void SetRight(float fRight) override;
		float GetRight() const override;

		void SetBottom(float fBottom) override;
		float GetBottom() const override;

		void Set(float fX, float fY, float fWidth, float fHeight) override;
		void Set2(float fLeft, float fTop, float fRight, float fBottom) override;

		bool Modified() const;
		void ModifyDone();

		bool CheckInsectionWith(const Rect* pRect) override;

	private:
		 RectGL();
		~RectGL() = default;

		template <typename T>
		friend void RefferRelease(T& refferer);
	};
}
#endif // !_H_RECT_GL_