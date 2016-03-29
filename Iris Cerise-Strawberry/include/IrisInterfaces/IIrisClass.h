#ifndef _H_IIRISCLASS_
#define _H_IIRISCLASS_

#include "IrisUnil/IrisValue.h"

class IIrisMethod;
class IIrisModule;
class IIrisInterface;
class IIrisContextEnvironment;
class IIrisValues;

class IrisClass;

class IIrisClass
{
private:
	IrisClass* m_pInternClass = nullptr;

public:

	typedef IrisValue(*IrisNativeFunction)(IrisValue&, IIrisValues*, IIrisValues*, IIrisContextEnvironment*);

public:

	IIrisClass() {}

	virtual IrisClass* GetInternClass() { return m_pInternClass; };

	virtual const char* NativeClassNameDefine() const = 0;
	virtual IIrisClass* NativeSuperClassDefine() const = 0;
	virtual IIrisModule* NativeUpperModuleDefine() const { return nullptr; };

	virtual int GetTrustteeSize(void* pNativePointer) = 0;

	virtual void* NativeAlloc() = 0;
	virtual void NativeFree(void* pNativePointer) = 0;
	virtual void NativeClassDefine() = 0;
	virtual void Mark(void* pNativePointer) { return; }

	virtual ~IIrisClass() = 0 {};

	friend class IrisClass;
	friend class IrisInterpreter;
};

#endif