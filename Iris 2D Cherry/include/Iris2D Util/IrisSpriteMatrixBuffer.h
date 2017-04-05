#ifndef _H_IRISSPRITEMATRIXBUFFER_
#define _H_IRISSPRITEMATRIXBUFFER_

#include "IrisCommon.h"

namespace Iris2D
{
	__declspec(align(16)) struct IrisSpriteMatrixBuffer {

		DirectX::XMMATRIX m_mxTransMatrix;
		DirectX::XMMATRIX m_mxRotMatrix;
		DirectX::XMMATRIX m_mxZoomMatrix;

		IrisSpriteMatrixBuffer() : m_mxTransMatrix(DirectX::XMMatrixIdentity()),
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

}
#endif // !_H_IRISSPRITEMATRIXBUFFER_

