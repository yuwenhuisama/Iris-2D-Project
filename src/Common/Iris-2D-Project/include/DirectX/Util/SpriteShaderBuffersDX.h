#ifndef _H_SPRITE_MATRIX_BUFFER_
#define _H_SPRITE_MATRIX_BUFFER_

#include "DirectX/Common.h"

namespace Iris2D
{
	__declspec(align(16)) struct SpriteVertexShaderBufferDX {

		DirectX::XMMATRIX m_mxTransMatrix;
		DirectX::XMMATRIX m_mxRotMatrix;
		DirectX::XMMATRIX m_mxZoomMatrix;
		DirectX::XMFLOAT2 m_f2OxOy { 0, 0 };

		SpriteVertexShaderBufferDX() : m_mxTransMatrix(DirectX::XMMatrixIdentity()),
									m_mxRotMatrix(DirectX::XMMatrixIdentity()),
									m_mxZoomMatrix(DirectX::XMMatrixIdentity())
		{

		}

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}
	};

	__declspec(align(16)) struct SpritePixelShaderBufferDX
	{
		DirectX::XMFLOAT4 m_f4SpriteRect{ 0.0f, 0.0f, 0.0f, 0.0f };
		DirectX::XMFLOAT4 m_f4Tone{ 0, 0, 0, 0 };
		float m_fOpacity = 255.0f;
		__int32 m_nMirror = 0;

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
#endif // !_H_SPRITE_MATRIX_BUFFER_

