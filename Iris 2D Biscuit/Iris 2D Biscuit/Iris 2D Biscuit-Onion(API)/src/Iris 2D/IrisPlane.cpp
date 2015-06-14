#include "IrisPlane.h"

namespace Iris2D{

	IrisPlane::IrisPlane(void)
	{
	}

	IrisPlane::IrisPlane(IIrisViewport* viewport)
	{
	}

	void IrisPlane::SetInitData(IIrisViewport* viewport){

	}

	bool IrisPlane::Disposed(IR_PARAM_RESULT_CT){
		return true;
	}

	void IrisPlane::Dispose(IR_PARAM_RESULT_CT){

	}

	IrisPlane::~IrisPlane(void)
	{
	}
}