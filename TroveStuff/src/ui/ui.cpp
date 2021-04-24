#include "ui.h"

bool UI::_visible = false;
bool UI::_framerateVisible = false;

void UI::Initialize()
{
	_visible = false;
	_framerateVisible = false;

	CreateStyle();

	Menu::Initialize();
}

void UI::RenderFPS()
{
	if (!_framerateVisible)
		return;

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowSize(ImVec2(100, 25));
	ImGui::Begin("FPS", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
	ImGui::End();
}

void UI::RenderMainMenuBar()
{

	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		ImGui::Selectable("Main Window", &Menu::_visible, 0, ImVec2(ImGui::CalcTextSize("Main Window", NULL, true).x, 0.0f)); //FIXME: buttons don't really work?
		ImGui::SameLine();

		ImGui::Selectable("Debug", &Menu::_debugVisible, 0, ImVec2(ImGui::CalcTextSize("Debug", NULL, true).x, 0.0f));
		ImGui::SameLine();

		ImGui::Selectable("Demo", &Menu::_demoVisible, 0, ImVec2(ImGui::CalcTextSize("Demo", NULL, true).x, 0.0f));
		//ImGui::SameLine();

		//Upper Right Corner
		//push it
		ImGui::SameLine(ImGui::GetWindowWidth() - 300 - ImGui::GetStyle().WindowPadding.x);
		ImGui::Selectable("FPS", &_framerateVisible, 0, ImVec2(ImGui::CalcTextSize("FPS", NULL, true).x, 0.0f));
		ImGui::SameLine();
		ImGui::Selectable("Unload", &g_Unload, 0, ImVec2(ImGui::CalcTextSize("Unload", NULL, true).x, 0.0f));
		ImGui::SameLine();
		ImGui::TextColored(_style.Colors[ImGuiCol_::ImGuiCol_Text], Utils::GetFullTimeDayString());

		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}

void UI::Render()
{
	CreateStyle();

	//Render Windows
	RenderFPS(); //Render FPS before everything else

	if (_visible)
	{
		RenderMainMenuBar();

		Menu::Render();
	}

	//Windows End
}

void SetCursor(bool vis)
{
	ImGui::GetIO().MouseDrawCursor = vis;
}

void UI::Show()
{
	_visible = true;
	SetCursor(_visible);
}

void UI::Hide()
{
	_visible = false;
	SetCursor(_visible);
}

int UI::Toggle()
{
	_visible = !_visible;
	SetCursor(_visible);

	return _visible;
}

void UI::CreateStyle()
{
	//TODO: UI::CreateStyle()
	ImGui::StyleColorsDark();
}