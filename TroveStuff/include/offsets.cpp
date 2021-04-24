#include "offsets.h"
#include <Windows.h>

int Offsets::moduleBase = 0;

void Offsets::Init()
{
	moduleBase = (int)GetModuleHandle(NULL);
}