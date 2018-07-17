#include "DirectX/Iris2D/IrisShaders/IrisShaderBase.h"
#include "DirectX/Iris2D/IrisD3DResourceManager.h"

namespace Iris2D
{
	bool IrisShaderBase::Initialize()
	{
		m_dwShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
		m_dwShaderFlag |= D3DCOMPILE_DEBUG;
#endif // DEBUG

		auto hResult = D3DCompileFromFile(
			ShaderFileDefine().c_str(),
			nullptr, 
			nullptr, 
			ShaderEntryFuncDefine().c_str(), 
			ShaderVersionDefine().c_str(),
			m_dwShaderFlag, 
			0, 
			&m_pShaderBuffer, 
			&m_pErrorBuffer
		);

		if (FAILED(hResult)) {
			if (m_pErrorBuffer) {
				OutputDebugStringA(static_cast<char*>(m_pErrorBuffer->GetBufferPointer()));
				SafeCOMRelease(m_pErrorBuffer);
			}
			return false;
		}

		if (m_pErrorBuffer) {
			SafeCOMRelease(m_pErrorBuffer);
		}

		if (!CreateShader(m_pShaderBuffer)) {
			return false;
		}

		if (!ShaderSubResourceDefine()) {
			return false;
		}

		return true;
	}
}
