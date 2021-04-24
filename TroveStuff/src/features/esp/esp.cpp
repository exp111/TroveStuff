#include "esp.h"

void ESP::Render()
{
	if (!config->ESP)
		return;

	if (!*(bool*)GetRelativeOffset(Offsets::inMultiplayer)) //TODO: get proper ingame
		return;

	Character* localPlayer = Character::GetCharacter(0);
	// 0 == localPlayer
	for (int i = 1; i < 64; i++) //TODO: get max players
	{
		Character* ply = Character::GetCharacter(i);
		if (ply == nullptr)
			continue;

		PlayerEntity* ent = ply->Entity;
		if (ent == nullptr) //isnull when choosing class //TODO: alive check?
			continue;

		//TODO: team check

		auto pos = WorldToScreen(ent->position);
		if (pos.IsNull()) //out of screen
			continue;

		//TODO: health esp?
		Color clr = Color(255, 0, 0);
		if (ply->Team->index == localPlayer->Team->index)
			clr = Color(0, 255, 0);

		std::wstring ws(ply->name);
		std::string name = std::string(ws.begin(), ws.end()); //TODO: print also class name
		renderer.RenderText(name, pos, ImGui::GetFontSize(), clr, true);
	}
}