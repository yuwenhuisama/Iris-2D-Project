#include "Iris 2D/IrisPlane.h"
#include "Iris 2D/IrisBitmap.h"
#include "Iris 2D/IrisViewport.h"
#include "Iris 2D/IrisColor.h"
#include "Iris 2D/IrisTone.h"
#include "Iris 2D/IrisSprite.h"

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