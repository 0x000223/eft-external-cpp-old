/*****************************************************************//**
 * \file   render.hpp
 * \brief  
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

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
	
	static ImFont* font_mbender;
	static ImFont* font_mbender_bold;

	
	static auto draw_text(ImVec2 pos, ImColor color, std::string text) -> void;

	static auto draw_text_stroke(ImVec2 pos, ImColor color, std::string text) -> void;
	
	static auto draw_line(ImVec2 from, ImVec2 to, ImColor color) -> void;

	static auto draw_line_stroke(ImVec2 from, ImVec2 to, ImColor color) -> void;
	
	static auto draw_rect(ImVec2 pos, ImVec2 length, ImColor color) -> void;

	static auto draw_rect_stroke(ImVec2 pos, ImVec2 length, ImColor color, ImColor outline_color = ImColor(0,0,0,255)) -> void;
	
	static auto draw_rect_filled(ImVec2 pos, ImVec2 length, ImColor color) -> void;

	static auto draw_edged_rect(ImVec2 pos, ImVec2 length, ImColor color, float percent = 0.4f, float thickness = 1.f, bool outline = true) -> void;

public:
	
	static void frame();
};

#endif
