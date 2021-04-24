#include "hooks.h"
#include <iostream>

decltype(Hooks::oRequest) Hooks::oRequest = nullptr;

std::uintptr_t Hooks::RequestAddr = NULL;
int base = 0;

int __fastcall Hooks::hkRequest(int _this, void* xmlRequest, void* param2)
{
	if (_this != (int)(base + 0xfa4f18))
		return oRequest(_this, xmlRequest, param2); // we fail here

	std::cout << "Request: " << (char*)(xmlRequest);
	
	auto result = oRequest(_this, xmlRequest, param2);


	return result;
}

void Hooks::hook()
{
	//Hooks::PresentAddr = (std::uintptr_t)(Utils::PatternScan(GetModuleHandle("gameoverlayrenderer.dll"), Signatures::Present) + 2);
	//Hooks::ResetAddr = (std::uintptr_t)(Utils::PatternScan(GetModuleHandle("gameoverlayrenderer.dll"), Signatures::Reset) + 2);
	base = (int)GetModuleHandle(NULL);
	Hooks::RequestAddr = (std::uintptr_t)(base + 0x9691a0);
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