#ifndef _H_RESULT_
#define _H_RESULT_

#include <string>
#include "Common/CompileConfigure.h"

#define IR_SUCCESS(r) ((r).resultType == ResultType.SUCCESS) 
#define IR_FAILD(r) ((r).resultType != ResultType.SUCCESS)
#define IR_MEM_ERROR(r) ((r).resultType == ResultType.MEM_ERROR)
#ifdef _WIN32
#define IR_SHOW_ERROR(r) ::MessageBoxW(nullptr, L"Error!", (r).wstrResultMsg.c_str(), nullptr);
#else
#define IR_SHOW_ERROR(r)
#endif

#define IR_PARAM _rParam
#define IR_PARAM_RESULT Result* IR_PARAM = nullptr
#define IR_PARAM_RESULT_CT Result* IR_PARAM
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->irResultType = res; \
			_rParam->wstrResultMsg = msg; \
		} \
	} while (0); \

namespace Iris2D {
	enum class ResultType {
		SUCCESS = 0,
		FAILED,
		MEM_ERROR,
	};

	struct Result {
	public:
		ResultType irResultType = ResultType::SUCCESS;
		std::wstring wstrResultMsg = L"";
	};
}

#endif // !_H_RESULT_

