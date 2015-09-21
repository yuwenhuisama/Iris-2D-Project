#ifndef _IRISENCRIPEDRESOURCEMANAGER_
#define _IRISENCRIPEDRESOURCEMANAGER_
#include "IrisGraphicsSourceExtract.h"
#include "GeneralEncriptySourceExtract.h"
#include "Iris2DSupports.h"
#include <list>

class IrisEncripedResourceManager
{
protected:

	list<IrisGraphicsSourceExtract*> m_lsExtracts;
	list<GeneralEncriptySourceExtract*> m_lsGenExtracts;

	IrisEncripedResourceManager();
	static IrisEncripedResourceManager* _instance;

public:
	
	static IrisEncripedResourceManager* Instance();

	void AddGraphResource(wstring strPackagePath, SafetyFunc pfFunc = NULL);
	void AddGeneralResource(wstring strPackagePath, SafetyFunc pfFunc = NULL);
	bool GetBitmapData(wstring wstrFilePath, char** ppData, int* nWidth, int* nHeight);
	bool GetGeneralData(wstring wstrFilePath, char** ppData, int* nSize);
	bool HaveGeneralSource(wstring wstrFilePath);
	bool HaveSource(wstring wstrFilePath);

	~IrisEncripedResourceManager();
};

#endif