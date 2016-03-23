#ifndef _H_IRISENCRIPEDRESOURCEMANAGER_
#define _H_IRISENCRIPEDRESOURCEMANAGER_
#include "Iris 2D Library.h"
#include "Iris2DSupports.h"
#include <list>

class IrisGraphicsSourceExtract;
class GeneralEncriptySourceExtract;
namespace Iris2D {
	class IrisEncripedResourceManager : public IIrisEncripedResourceManager
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
};
#endif