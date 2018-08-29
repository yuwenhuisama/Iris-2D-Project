#ifndef _H_RESULT_
#define _H_RESULT_

#include "Common/CompileConfigure.h"
#include <cwchar>

#ifdef __cplusplus
extern "C" {
#endif
	enum  ResultCode {
		IRR_Success = 0,
		IRR_OpenGLInitializeFailed,
		IRR_WindowInitializeFailed,
		IRR_TextureSettingInitializeFailed,
		IRR_GraphicsInitializeFailed,
		IRR_ShaderInitializeFailed,
		IRR_OpenGLVertexBufferCreateFailed,
		IRR_EffectInitializeFailed,
		IRR_EffectUpdateFailed,
		IRR_RenderBufferCreateFailed,
		IRR_D2DInitializeFailed,
		IRR_D3DInitializeFailed,
		IRR_D2DOperationFailed,
		IRR_TextureOutputFailed,


		IRR_XXXXXX
	};
#ifdef __cplusplus
}
#endif

#define IR_SUCCESS(result) (result == IRR_Success)
#define IR_FAILED(result) (result != IRR_Success)


#endif // !_H_RESULT_
