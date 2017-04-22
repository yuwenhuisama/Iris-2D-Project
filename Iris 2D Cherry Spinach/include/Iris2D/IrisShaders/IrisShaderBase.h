#ifndef _H_IRISSHADERBASE_
#define _H_IRISSHADERBASE_

#include "../../IrisCommon.h"

namespace Iris2D
{
	class IrisShaderBase
	{
	private:
		ID3DBlob* m_pShaderBuffer = nullptr;
		ID3DBlob* m_pErrorBuffer = nullptr;
		DWORD m_dwShaderFlag = 0;

	public:
		IrisShaderBase() = default;

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
		virtual ~IrisShaderBase() = default;
	};

}
#endif // !_H_IRISSHADERBASE_