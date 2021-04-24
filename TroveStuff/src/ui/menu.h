#pragma once

#define NOMINMAX
#include <Windows.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <string>
#include <chrono>

namespace Menu
{
	void Initialize();

	void Render();
	void RenderMainMenu();
	void RenderDebug();
	void RenderDemo();

	void Show();
	void Hide();
	void Toggle();

	extern bool _visible;
	extern bool _debugVisible;
	extern bool _demoVisible;
};