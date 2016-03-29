#ifndef _H_IRISPOINTER_
#define _H_IRISPOINTER_

//* Always Needed
#include "IrisLangLibrary.h"
#pragma comment(lib, "IrisLangLibrary.lib")

//* User's Extention Class
#include "IrisPointerTag.h"

class IrisPointer : public IIrisClass
{
public:
	// Define native initialize method of this class
	static IrisValue InitializeFunction(IrisValue& ivObj, IIrisValues* ivsValues, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue Get(IrisValue& ivObj, IIrisValues* ivsValues, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue Set(IrisValue& ivObj, IIrisValues* ivsValues, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

	static IrisValue GetLength(IrisValue& ivObj, IIrisValues* ivsValues, IIrisValues* ivsVariableValues, IIrisContextEnvironment* pContextEnvironment);

public:
	void Mark(void* pNativeObjectPointer) {}

	const char* NativeClassNameDefine() const;

	IIrisClass* NativeSuperClassDefine() const;

	// Overwrite virtual method GetTrustteeSize: To tell Iris how much memory has been malloced (GC will use this information).
	int GetTrustteeSize(void* pNativePointer);

	// Overwrite virtual method NativeAlloc : To give Iris a native object, and Iris will create an Object to link to it.
	void* NativeAlloc();

	// Overwrite virtual method NativeFree : When Iris's GC release a object of this class, and native object linked to it should also be released.
	void NativeFree(void* pNativePointer);

	// Overwrite virtual method NativeClassDefine : To add instance method/class method/getter/setter and others into this class.
	void NativeClassDefine();

	IrisPointer();
	~IrisPointer();
};

#endif