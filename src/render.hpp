
#ifndef RENDER_HPP
#define RENDER_HPP

#include <cstdint>

#include "render_backend.hpp"
#include "menu.hpp"
#include "settings.hpp"

struct render
{
private:

	static float clear_color[4];
	
	static int window_height, window_width;
	
	static ImFont* font_mbender;
	static ImFont* font_mbender_bold;
	
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static auto overlay_window() -> void;
	
	static auto draw_text(ImVec2 pos, ImColor color, std::string text) -> void;

	static auto draw_text_stroke(ImVec2 pos, ImColor color, std::string text) -> void;
	
	static auto draw_line(ImVec2 from, ImVec2 to, ImColor color) -> void;

	static auto draw_line_stroke(ImVec2 from, ImVec2 to, ImColor color) -> void;
	
	static auto draw_rect(ImVec2 pos, ImVec2 length, ImColor color) -> void;

	static auto draw_rect_stroke(ImVec2 pos, ImVec2 length, ImColor color, ImColor outline_color = ImColor(0,0,0,255)) -> void;
	
	static auto draw_rect_filled(ImVec2 pos, ImVec2 length, ImColor color) -> void;

	static auto draw_edged_rect(ImVec2 pos, ImVec2 length, ImColor color, float percent = 0.4f, float thickness = 1.f, bool outline = true) -> void;

public:
	
	static auto init() -> BOOL;

	static auto terminate() -> BOOL;

	static auto render_frame() -> void;
};

#endif
