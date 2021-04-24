#include "main.h"
#include "hooks.h"

bool g_Unload = false;

DWORD WINAPI onDllAttach(LPVOID base)
{
	Utils::AttachConsole();

	Offsets::Init();
	Hooks::hook();
	
	while (!g_Unload)
	{
		Sleep(1000);
	}

	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);

	//Should be unreachable
	return true;
}

BOOL WINAPI onDllDetach()
{
	//Utils::DetachConsole();

	Hooks::unhook();
	return true;
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_  LPVOID    lpvReserved
)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDll);
		CreateThread(nullptr, 0, onDllAttach, hinstDll, 0, nullptr);
		return TRUE;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return onDllDetach();
		return TRUE;
	default:
		return TRUE;
	}
}