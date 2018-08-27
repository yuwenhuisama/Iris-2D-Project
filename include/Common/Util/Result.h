#ifndef _H_RESULT_
#define _H_RESULT_

#include "Common/CompileConfigure.h"
#include <cwchar>

#ifdef _WIN32
#define IR_SHOW_ERROR(r) ::MessageBoxW(NULL, L"Error!", (r)->m_wszResultMsg, NULL);
#else
#define IR_SHOW_ERROR(r)
#endif

#define IR_PARAM _rParam
#define IR_PARAM_RESULT IR_Result* IR_PARAM = NULL
#define IR_PARAM_RESULT_CT IR_Result* IR_PARAM

#if IR_COMPILE_USE_RESULT_REPORT
#ifdef _MSC_VER
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->m_irResultType = res; \
			wcscpy_s(_rParam->m_wszResultMsg, msg); \
		} \
	} while (0);
#else
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->m_irResultType = res; \
			wcscpy(_rParam->m_wszResultMsg, msg); \
		} \
	} while (0);
#endif // _MSC_VER

#define IR_SUCCESS(r) ((r) && (r)->m_irResultType == IR_RESULT_SUCCESS) 
#define IR_FAILD(r) ((r) && (r)->m_irResultType != IR_RESULT_SUCCESS)

#define IR_DECLARE_RESULT_CHECKER(param) \
	IR_Result param;\
	IR_PARAM_SET_RESULT(&param, L"");

#else

#define IR_SUCCESS(r) false
#define IR_FAILD(r) false

#define IR_PARAM_SET_RESULT(res, msg)

#define IR_DECLARE_RESULT_CHECKER(param)

#endif // IR_COMPILE_USE_RESULT_REPORT

extern "C" {
	enum IR_ResultType {
		IR_RESULT_SUCCESS = 0,
		IR_RESULT_FAILED,
		IR_RESULT_MEM_ERROR,
	};

	#pragma pack(push, 8)
	struct IR_Result {
		IR_ResultType m_irResultType;
		wchar_t m_wszResultMsg[512];
	};
	#pragma pack(pop)
}

#endif // !_H_RESULT_
