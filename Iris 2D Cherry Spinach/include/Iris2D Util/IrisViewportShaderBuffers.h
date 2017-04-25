#ifndef _H_IRISVIEWPORTSHADERBUFFER_
#define _H_IRISVIEWPORTSHADERBUFFER_

#include "IrisCommon.h"

namespace Iris2D
{
	__declspec(align(16)) struct IrisViewportVertexShaderBuffer
	{
		DirectX::XMMATRIX m_mxTransMatrix = DirectX::XMMatrixIdentity();
		DirectX::XMFLOAT2 m_f2OxOy{ 0, 0 };

		void* operator new(size_t i)
		{
			return _mm_malloc(i, 16);
		}

		void operator delete(void* p)
		{
			_mm_free(p);
		}
	};

	__declspec(align(16)) struct IrisViewportPixelShaderBuffer
	{
		DirectX::XMFLOAT4 m_f4ViewportRect{ 0.0f, 0.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT4 m_f4Tone { 0.0f, 0.0f, 0.0f, 0.0f };

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
#endif // !_H_IRISVIEWPORTSHADERBUFFER_

