#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <string>
#include <sstream>
#include <defs.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize();

	void BeginScene();
	void EndScene();

	float RenderText(const std::string& text, const Vector2<float>& position, float size, Color color, bool center = false);
	void RenderLine(const ImVec2& from, const ImVec2& to, Color color, float thickness = 1.0f);
	void RenderCircle(const ImVec2& position, float radius, Color color, float thickness = 1.0f, uint32_t segments = 16);
	void RenderCircleFilled(const ImVec2& position, float radius, Color color, uint32_t segments = 16);
	void RenderRect(const ImVec2& from, const ImVec2& to, Color color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);
	void RenderRectFilled(const ImVec2& from, const ImVec2& to, Color color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
	//void RenderImage(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, Color color);
	//void RenderImageRounded(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);

private:
	ImFont* m_pFont;
};