#ifndef _H_IRISVALUE_
#define _H_IRISVALUE_
#include <vector>
using namespace std;

class IrisObject;
class IrisValue
{
private:
	IrisObject* m_pObject;
public:
	IrisValue();
	~IrisValue();

	IrisObject* GetObject();
	void SetObject(IrisObject* pObject);

public:
	static IrisValue WrapObjectPointerToIrisValue(IrisObject* pObjectPointer);
	void* GetInstanceNativePointer();

	bool operator == (const IrisValue& ivValue){
		return ivValue.m_pObject == m_pObject;
	}

	bool operator != (const IrisValue& ivValue) {
		return !(*this == ivValue);
	}

	//bool operator < (const IrisValue& ivValue);

	friend class IrisInterpreter;
	friend class IrisClass;
	friend class IrisModule;
	friend class IrisMethod;
	friend class IrisInteger;
	friend class IrisFloat;
	friend class IrisString;
	friend class IrisObject;
};

typedef vector<IrisValue> IrisValues;

enum class CallerSide {
	Inside = 0,
	Outside,
};

#endif