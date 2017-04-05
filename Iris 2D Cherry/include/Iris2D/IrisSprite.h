#ifndef _H_IRISSPRITE_

#include "../IrisCommon.h"
#include "Iris2D Util/IrisSpriteMatrixBuffer.h"

namespace Iris2D
{
	class IrisBitmap;
	__declspec(align(16)) class IrisSprite
	{
	private:

		const float c_fPI = 3.14159f;
		const float c_fArcUnit = c_fPI / 180.0f;

		IrisBitmap* m_pBitmap = nullptr;
		ID3D11Buffer* m_pVertexBuffer = nullptr;

		IrisSpriteMatrixBuffer m_mbMatrixBuffer;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;
		float m_fAngle = 0.0f;
		float m_fZoomX = 1.0f;
		float m_fZoomY = 1.0f;

		bool m_bPositionDirtyFlag = false;
		bool m_bAngleDirtyFlag = false;
		bool m_bZoomDirtyFlag = false;

	public:
		static IrisSprite* Create();
		static void Release(IrisSprite*& pSprite);

		static void InnerRelease(IrisSprite* pSprite);

	public:
		void SetBitmap(IrisBitmap* pBitmap);
		IrisBitmap* GetBitmap() const;

		void SetX(float fX);
		float GetX() const;

		void SetY(float fY);
		float GetY() const;

		void SetZ(float fZ);
		float GetZ() const;

		void SetAngle(float fAngle);
		float GetAngle() const;

		void SetRoomX(float fZoomX);
		float GetRoomX() const;

		void SetRoomY(float fZoomY);
		float GetRoomY() const;

		void Update();
		void Render();

	private:
		IrisSprite() = default;
		~IrisSprite();

		bool CreateSpriteVertexBuffer();

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}

	};
}


#endif // !_H_IRISSPRITE_
