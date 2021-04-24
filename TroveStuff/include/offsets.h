#pragma once

#define GetRelativeOffset(offset) (Offsets::moduleBase + offset)
namespace Offsets
{
	void Init();
	extern int moduleBase;
	static int RequestAddr = 0x9691a0;
}
namespace Signatures
{
	//static const char* Present = "FF 15 ? ? ? ? 8B F8 85 DB";//"gameoverlayrenderer.dll" //+2
	//static const char* Reset = "FF 15 ? ? ? ? 8B F8 85 FF 78 18";//"gameoverlayrenderer.dll" //+2
}