#include "menu.h"
#include "offsets.h"
#include "../config.h"

bool Menu::_visible = true;
bool Menu::_debugVisible = false;
bool Menu::_demoVisible = false;

void Menu::Initialize()
{
	_visible = true;
	_debugVisible = false;
}

void Menu::Render()
{
	RenderMainMenu();
	RenderDebug();
	RenderDemo();
}

void Menu::RenderMainMenu()
{
	if (!_visible)
		return;

	ImGui::Begin("Menu");
	ImGui::Text("Hello World!");
	ImGui::Separator();
	ImGui::Checkbox("Heroes Enabled", (bool*)(Offsets::moduleBase + Offsets::bHeroesEnabled));
	ImGui::InputInt("Respawn Val", (int*)(Offsets::moduleBase + Offsets::iHeroRespawnVal));
	ImGui::InputInt("Unlock Val", (int*)(Offsets::moduleBase + Offsets::iHeroUnlockVal));
	ImGui::Separator();
	ImGui::Checkbox("ESP", &config->ESP);

	ImGui::End();
}

void Menu::RenderDebug()
{
	if (!_debugVisible)
		return;

	ImGui::Begin("Debug");

	ImGui::End();
}

void Menu::RenderDemo()
{
	if (!_demoVisible)
		return;

	ImGui::ShowDemoWindow();
}

void Menu::Show()
{
	_visible = true;
}

void Menu::Hide()
{
	_visible = false;
}

void Menu::Toggle()
{
	_visible = !_visible;
}