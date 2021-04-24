#pragma once

#define GetRelativeOffset(offset) (Offsets::moduleBase + offset)
namespace Offsets
{
	void Init();
	extern int moduleBase;
	static int bHeroesEnabled = 0x1a62ee3;
	static int iHeroRespawnVal = 0x1a62f18;
	static int iHeroUnlockVal = 0x3e804c;
	static int ScreenResX = 0x1a56c34;
	static int ScreenResY = 0x1a56c30;
	static int cameraManager = 0x1a30324;
	static int viewMatrix = 0x4eed20;
	static int characterList = 0x1a30334;
	static int inMultiplayer = 0x1aad4b7;
}
namespace Signatures
{
	static const char* Present = "FF 15 ? ? ? ? 8B F8 85 DB";//"gameoverlayrenderer.dll" //+2
	static const char* Reset = "FF 15 ? ? ? ? 8B F8 85 FF 78 18";//"gameoverlayrenderer.dll" //+2
}