#ifndef _H_IIRISOBJECT_
#define _H_IIRISOBJECT_

#include "IrisUnil/IrisValue.h"

class IIrisClass;
class IIrisContextEnvrionment;
class IIrisValues;
class IIrisObject
{
public:

	IIrisObject() {}
	
	//virtual bool IsUsed() = 0;

	//virtual void Fix() = 0;
	//virtual void Unfix() = 0;
	//virtual bool IsFixed() = 0;

	//virtual void SetPermanent(bool bFlag) = 0;
	//virtual bool IsPermanent() = 0;

	//virtual void SetHash(size_t nHash) = 0;
	//virtual size_t GetHash() = 0;
	//virtual bool Hashed() = 0;

	//virtual int GetObjectID() = 0;
	//virtual IIrisClass* GetClass() = 0;
	//virtual void SetClass(IIrisClass* pClass) = 0;

	//virtual const IrisValue& GetInstanceValue(const string& strInstanceValueName, bool& bResult)= 0; 

	//virtual void AddInstanceValue(const string& strInstanceValueName, const IrisValue& ivValue) = 0;
	////virtual	void AddSingleInstanceMethod(IrisMethod* pMethod) = 0;

	//virtual void Mark()= 0;
	//virtual void ClearMark() = 0;

	//virtual void* GetNativeObject() = 0;
	//virtual void SetNativeObject(void* pNativeObject) = 0 ;

	virtual ~IIrisObject() = 0 {};
};

#endif