#ifndef _H_RESULT_
#define _H_RESULT_

#include <string>
#include "Common/CompileConfigure.h"

#define IR_SUCCESS(r) ((r)->m_resultType == IR_SUCCESS) 
#define IR_FAILD(r) ((r)->m_resultType != IR_SUCCESS)
#define IR_MEM_ERROR(r) ((r)->m_resultType == IR_MEM_ERROR)
#ifdef _WIN32
#define IR_SHOW_ERROR(r) ::MessageBoxW(NULL, L"Error!", (r)->wstrResultMsg, NULL);
#else
#define IR_SHOW_ERROR(r)
#endif

#define IR_PARAM _rParam
#define IR_PARAM_RESULT IR_Result* IR_PARAM = NULL
#define IR_PARAM_RESULT_CT IR_Result* IR_PARAM
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->irResultType = res; \
			_rParam->wstrResultMsg = msg; \
		} \
	} while (0); \

enum IR_ResultType {
	IR_SUCCESS = 0,
	IR_FAILED,
	IR_MEM_ERROR,
};

struct IR_Result {
public:
	IR_ResultType m_irResultType;
	wchar_t* m_wstrResultMsg;
};


#endif // !_H_RESULT_
