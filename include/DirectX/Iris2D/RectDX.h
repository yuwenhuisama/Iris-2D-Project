#ifndef _H_RECT_DX_
#define _H_RECT_DX_

#include "DirectX/Common.h"
#include "Common/Iris2D/IRect.h"
#include "Common/Util/RefCounter.h"
#include "Common/Iris2D/Proxied.h"

#include "Common/Util/DirtyChecker.h"

namespace Iris2D
{
	class Rect;
	class RectDX : public Proxied<Rect>, public IRect, public RefCounter
	{
	private:
		DirectX::XMFLOAT4 m_f4Rect{ 0.0f, 0.0f, 0.0f, 0.0f };
		//bool m_bModifyDirtyFlag = false;

		DirtyChecker m_dcChecker;
		DirtyChecker::DirtyCheckerHandler m_hModified = 0;

	public:
	
		static RectDX* Create(float fX, float fY, float fWidth, float fHeight);

		static RectDX* Create2(float fLeft, float fTop, float fRight, float fBottom);

		static void Release(RectDX*& pRect);

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

		void SetRight(float fRight);

		float GetTop() const;

		void SetBottom(float fBottom);
	
		float GetRight() const;

		void SetTop(float fTop);
	
		float GetBottom() const;
		
		void Set(float fX, float fY, float fWidth, float fHeight);
	
		void Set2(float fLeft, float fTop, float fRight, float fBottom);

		bool Modified();
		void ModifyDone();

	private:
		RectDX() = default;
		~RectDX() = default;
	};
}
#endif // !_H_RECT_DX_
