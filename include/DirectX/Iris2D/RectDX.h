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

		void SetRight(float fRight) override;
		float GetTop() const override;

		void SetBottom(float fBottom) override;
		float GetRight() const override;

		void SetTop(float fTop) override;
		float GetBottom() const override;
		
		void Set(float fX, float fY, float fWidth, float fHeight) override;
		void Set2(float fLeft, float fTop, float fRight, float fBottom) override;

		bool Modified() const;
		void ModifyDone();

	private:
		RectDX();
		~RectDX() = default;
	};
}
#endif // !_H_RECT_DX_
