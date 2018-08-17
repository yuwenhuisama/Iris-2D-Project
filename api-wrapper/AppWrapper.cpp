#define LIBRARY_EXPORTS
#include "AppWrapper.h"

EXPORT_API APP_HANDLE App_GetInstance() {
	return Iris2D::AppFactory::GetApplication();
}

EXPORT_API BOOL App_Initialize1(APP_HANDLE hHandle, HINSTANCE hInstance, unsigned int nWidth, unsigned int nHeight, App_GameFunc pfGameFunc, wchar_t* wszTitle) {
	auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->Initialize(hInstance, nWidth, nHeight, reinterpret_cast<Iris2D::GameFunc>(pfGameFunc), wszTitle);
}

EXPORT_API BOOL App_Initialize2(APP_HANDLE hHandle, App_AppStartupInfo* pInfo) {
	Iris2D::AppStartupInfo asiInfo(pInfo->m_hInstance, pInfo->nShowCmd, pInfo->m_nX, pInfo->m_nY, pInfo->m_nWidth, pInfo->m_nHeight, reinterpret_cast<Iris2D::GameFunc>(pInfo->m_pfFunc()), pInfo->m_wstrTitle);
	auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->Initialize(&asiInfo);
}

EXPORT_API BOOL App_Run(APP_HANDLE hHandle) {
	auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->Run();
}

EXPORT_API void App_Release(APP_HANDLE hHandle) {
	auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	pApplication->Release();
}

EXPORT_API BOOL App_IsUninitialized(APP_HANDLE hHandle) {
	const auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->IsUninitialized();
}

EXPORT_API BOOL App_IsRunning(APP_HANDLE hHandle) {
	const auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->IsRunning();
}

EXPORT_API BOOL App_IsQuited(APP_HANDLE hHandle) {
	const auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->IsQuited();
}

EXPORT_API void App_Quite(APP_HANDLE hHandle) {
	auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	pApplication->Quite();
}

EXPORT_API float App_GetTimeDelta(APP_HANDLE hHandle) {
	const auto pApplication = reinterpret_cast<Iris2D::Application*>(hHandle);
	return pApplication->GetTimeDelta();
}
