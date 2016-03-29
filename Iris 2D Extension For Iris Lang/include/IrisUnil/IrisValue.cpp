#include "IrisUnil/IrisValue.h"
#include "IrisInterfaces/IIrisObject.h"

IrisValue::IrisValue() {}

IrisValue::~IrisValue() {}

IrisValue IrisValue::WrapObjectPointerToIrisValue(IIrisObject * pObjectPointer) {
	IrisValue ivValue;
	ivValue.m_pObject = pObjectPointer;
	return ivValue;
}

//void * IrisValue::GetInstanceNativePointer() const {
//	return m_pObject->GetNativeObject();
//}
