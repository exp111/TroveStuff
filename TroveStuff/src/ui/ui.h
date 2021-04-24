#pragma once

#define NOMINMAX
#include <Windows.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <string>
#include <chrono>

#include "../main.h"
#include "../hooks.h"

#include "../helpers/utils.h"
#include "menu.h"

namespace UI
{
	void Initialize();

	void RenderFPS();
	void RenderMainMenuBar();
	void Render();

	void Show();
	void Hide();
	int Toggle();

	static ImGuiStyle _style;
	extern bool _visible;
	extern bool _framerateVisible;

	void CreateStyle();
};