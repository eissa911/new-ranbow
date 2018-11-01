#include <Windows.h>
#include "Main.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reasonForCall, LPVOID lpReserved) {
	switch(reasonForCall) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main::Start), NULL, NULL, NULL);
		break;

	case DLL_PROCESS_DETACH:
		Main::Stop();
		break;
	}
	return TRUE;
}