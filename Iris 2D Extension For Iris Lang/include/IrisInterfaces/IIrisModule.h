#ifndef _H_IIRISMODULE_
#define _H_IIRISMODULE_

class IrisModule;
class IIrisModule
{
private:
	IrisModule* m_pInternModule = nullptr;

public:

	IrisModule* GetInternModule() { return m_pInternModule; }

	IIrisModule() {}
	virtual const char* NativeModuleNameDefine() const = 0;
	virtual IIrisModule* NativeUpperModuleDefine() const = 0;
	virtual void NativeModuleDefine() = 0;
	virtual ~IIrisModule() = 0 {};

	friend class IrisModule;
	friend class IrisInterpreter;
};

#endif