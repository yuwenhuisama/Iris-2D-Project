#ifndef _H_IRISVALUE_
#define _H_IRISVALUE_
#include <vector>
using namespace std;

class IIrisObject;
class IrisValue
{
private:
	IIrisObject* m_pObject = nullptr;
public:
	IrisValue();
	~IrisValue();

	inline IIrisObject* GetIrisObject() const { return m_pObject; }
	inline void SetIrisObject(IIrisObject* pObject) { m_pObject = pObject; }

public:
	static IrisValue WrapObjectPointerToIrisValue(IIrisObject* pObjectPointer);

	//void* GetInstanceNativePointer() const;
	
	bool operator == (const IrisValue& ivValue) const{
		return ivValue.m_pObject == m_pObject;
	}

	bool operator != (const IrisValue& ivValue) const {
		return !(*this == ivValue);
	}
};

#endif