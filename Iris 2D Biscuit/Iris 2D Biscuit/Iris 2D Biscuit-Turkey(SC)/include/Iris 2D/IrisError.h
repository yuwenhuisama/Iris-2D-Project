#ifndef _IRISERROR_H_
#define _IRISERROR_H_

#include <string>
using namespace std;

#define IR_SUCCESS(r) ((r).resultType == IR_RSUCCESS)
#define IR_FAILD(r) ((r).resultType != IR_RSUCCESS)
#define IR_MEM_ERROR(r) ((r).resultType == IR_RMEM_ERROR)
#define IR_SHOW_ERROR(r) ::MessageBox(NULL, L"Error!", (r).resultMsg, NULL);

#define IR_PARAM _rParam
#define IR_PARAM_RESULT IrisResult* IR_PARAM = NULL
#define IR_PARAM_RESULT_CT IrisResult* IR_PARAM
#define IR_PARAM_SET_RESULT(res, msg) \
	do { \
		if(_rParam){ \
			_rParam->resultType = res; \
			_rParam->resultMsg = msg; \
		} \
	} while (0); \

namespace Iris2D {
	enum IR_RESULT{
		IR_RSUCCESS = 0,
		IR_RFAILED,
		IR_RMEM_ERROR,
	};

	struct IrisResult {
	public:
		IR_RESULT resultType;
		wstring resultMsg;

		IrisResult(){
			resultType = IR_RSUCCESS;
			resultMsg = L"";
		}
	};
}

#endif