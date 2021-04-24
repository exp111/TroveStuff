#include "hooks.h"
#include <iostream>
#include <intrin.h>

decltype(Hooks::oRequest) Hooks::oRequest = nullptr;

std::uintptr_t Hooks::RequestAddr = NULL;

int __fastcall Hooks::hkRequest(void* _this, void* edx, void* xmlRequest, void* param2)
{
	int returnAddress = (int)_ReturnAddress();
	//if ((int)returnAddress != (int)(Offsets::moduleBase + 0x942429))
	//if ((int)_this != *(int*)(Offsets::moduleBase + 0xfa4f18))
	//	return oRequest(_this, xmlRequest, param2); // we fail here

	
	
	auto result = oRequest(_this, xmlRequest, param2);

	if (xmlRequest != 0 && (*(int*)xmlRequest) != 0)
	{
		Utils::ConsolePrint("%i", xmlRequest);
		//std::string req = *(char**)(xmlRequest);
		//Utils::ConsolePrintDirect(req.c_str());
		//Utils::ConsolePrint("\n");
	}
	

	return result;
}

void Hooks::hook()
{
	//Hooks::PresentAddr = (std::uintptr_t)(Utils::PatternScan(GetModuleHandle("gameoverlayrenderer.dll"), Signatures::Present) + 2);
	//Hooks::ResetAddr = (std::uintptr_t)(Utils::PatternScan(GetModuleHandle("gameoverlayrenderer.dll"), Signatures::Reset) + 2);
	
	Hooks::RequestAddr = (std::uintptr_t)(Offsets::moduleBase + Offsets::RequestAddr);
	// Init Detours
	MH_Initialize();


	MH_CreateHook((void*)Hooks::RequestAddr, &Hooks::hkRequest, (void**)(&Hooks::oRequest));
	// Hooks
	//MH_CreateHook(**(void***)Hooks::PresentAddr, &Hooks::hkPresent, (void**)(&Hooks::oPresent));
	//MH_CreateHook(**(void***)Hooks::ResetAddr, &Hooks::hkReset, (void**)(&Hooks::oReset));

	MH_EnableHook(MH_ALL_HOOKS);
}

void Hooks::unhook()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	// ImGui Shutdown //TODO: move
	/*ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();*/
}