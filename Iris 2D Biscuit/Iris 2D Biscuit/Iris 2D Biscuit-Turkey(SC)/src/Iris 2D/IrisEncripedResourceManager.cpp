#include "IrisEncripedResourceManager.h"

IrisEncripedResourceManager* IrisEncripedResourceManager::_instance = NULL;

IrisEncripedResourceManager* IrisEncripedResourceManager::Instance(){
	if (_instance == NULL)
		_instance = new IrisEncripedResourceManager();
	return _instance;
}

IrisEncripedResourceManager::IrisEncripedResourceManager() : m_lsExtracts(), m_lsGenExtracts()
{
}

void IrisEncripedResourceManager::AddGeneralResource(wstring strPackagePath, SafetyFunc pfFunc){
	GeneralEncriptySourceExtract* geseObj = new GeneralEncriptySourceExtract();
	geseObj->InitPackageData(WStringToString(strPackagePath), pfFunc);
	m_lsGenExtracts.push_back(geseObj);
}

void IrisEncripedResourceManager::AddGraphResource(wstring strPackagePath, SafetyFunc pfFunc){
	IrisGraphicsSourceExtract* igseObj = new IrisGraphicsSourceExtract();
	igseObj->InitPackageData(WStringToString(strPackagePath), pfFunc);
	m_lsExtracts.push_back(igseObj);
}

bool IrisEncripedResourceManager::GetBitmapData(wstring wstrFilePath, char** ppData, int* nWidth, int* nHeight){
	list<IrisGraphicsSourceExtract*>::iterator it;
	for (it = m_lsExtracts.begin(); it != m_lsExtracts.end(); ++it){
		if ((*it)->IsHaveFile(WStringToString(wstrFilePath))) {
			(*it)->GetBitmapData(WStringToString(wstrFilePath), ppData, nWidth, nHeight);
			return true;
		}
	}
	return false;
}

bool IrisEncripedResourceManager::HaveSource(wstring wstrFilePath){
	list<IrisGraphicsSourceExtract*>::iterator it;
	for (it = m_lsExtracts.begin(); it != m_lsExtracts.end(); ++it){
		if ((*it)->IsHaveFile(WStringToString(wstrFilePath))) {
			return true;
		}
	}
	return false;
}

bool IrisEncripedResourceManager::GetGeneralData(wstring wstrFilePath, char** ppData, int* nSize){
	list<GeneralEncriptySourceExtract*>::iterator it;
	for (it = m_lsGenExtracts.begin(); it != m_lsGenExtracts.end(); ++it){
		if ((*it)->IsHaveFile(WStringToString(wstrFilePath))) {
			(*it)->GetGeneralData(WStringToString(wstrFilePath), ppData, nSize);
			return true;
		}
	}
	return false;
}

bool IrisEncripedResourceManager::HaveGeneralSource(wstring wstrFilePath){
	list<GeneralEncriptySourceExtract*>::iterator it;
	for (it = m_lsGenExtracts.begin(); it != m_lsGenExtracts.end(); ++it){
		if ((*it)->IsHaveFile(WStringToString(wstrFilePath))) {
			return true;
		}
	}
	return false;
}

IrisEncripedResourceManager::~IrisEncripedResourceManager()
{
}
