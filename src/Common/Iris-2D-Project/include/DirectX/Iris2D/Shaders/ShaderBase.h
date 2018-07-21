#ifndef _H_SHADER_BASE_
#define _H_SHADER_BASE_

#include "DirectX/Common.h"

namespace Iris2D
{
	class ShaderBase
	{
	private:
		ID3DBlob* m_pShaderBuffer = nullptr;
		ID3DBlob* m_pErrorBuffer = nullptr;
		DWORD m_dwShaderFlag = 0;

	public:
		ShaderBase() = default;

		virtual bool Initialize();

	protected:
		virtual std::wstring ShaderFileDefine() = 0;
		virtual std::string ShaderEntryFuncDefine() = 0;
		virtual std::string ShaderVersionDefine() = 0;
		virtual bool ShaderSubResourceDefine() = 0;
		virtual bool CreateShader(ID3DBlob* pBlob) = 0;

	public:
		virtual bool SetToContext() = 0;
		virtual bool Release() = 0;

	public:
		virtual ~ShaderBase() = default;
	};

}
#endif // !_H_SHADER_BASE_