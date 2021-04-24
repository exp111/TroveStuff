#pragma once
#include <Windows.h>
#include <cstdint>
#include <minhook/minhook.h>
//#include <renderer.h>
#include "main.h"
#include "helpers/utils.h"
#include "offsets.h"
//#include "ui/ui.h"
//#include "features/features.h"
#include <algorithm>

namespace Hooks
{
	extern int(__thiscall*  oRequest)(void*, void*, void*);

	int __fastcall hkRequest(void* _this, void* edx,  void* xmlRequest, void* param2);

	extern std::uintptr_t RequestAddr;
	

	extern void hook();
	extern void unhook();
}