#ifndef _H_IRISRESULT

#include <string>
#include "Common/Iris2DCompileConfigure.h"

#define IR_SUCCESS(r) ((r).resultType == IrisResultType.SUCCESS) 
#define IR_FAILD(r) ((r).resultType != IrisResultType.SUCCESS)
#define IR_MEM_ERROR(r) ((r).resultType == IrisResultType.MEM_ERROR)
#define IR_SHOW_ERROR(r) ::MessageBoxW(nullptr, L"Error!", (r).wstrResultMsg.c_str(), nullptr);

#define IR_PARAM _rParam
#define IR_PARAM_RESULT IrisResult* IR_PARAM = nullptr
#define IR_PARAM_RESULT_CT IrisResult* IR_PARAM
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->irResultType = res; \
			_rParam->wstrResultMsg = msg; \
		} \
	} while (0); \

namespace Iris2D {
	enum class IrisResultType {
		SUCCESS = 0,
		FAILED,
		MEM_ERROR,
	};

	struct IrisResult {
	public:
		IrisResultType irResultType = IrisResultType::SUCCESS;
		std::wstring wstrResultMsg = L"";
	};
}

#endif // !_H_IRISRESULT

