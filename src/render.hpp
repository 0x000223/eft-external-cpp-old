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
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

namespace render {

	/**
	 * @brief
	 */
	static float clear_color[4] = { 0.f, 0.f, 0.f, 0.f };

	/**
	 * @brief
	 */
	static bool is_menu_rendered = false;

	/**
	 * @brief Set default menu style
	 */
	void menu_set_style_default();

	/**
	 * @brief Set main menu interface 
	 */
	static void menu_window_main();

	/**
	 * @brief
	 */
	//static void menu_tab_visual();

	/**
	 * @brief 
	 */
	//static void menu_tab_aim();

	/**
	 * @brief
	 */
	static void overlay();

	/**
	 * @brief
	 */
	static void text(const ImVec2& pos, const ImColor& color, const std::string& text);

	/**
	 * @brief
	 */
	static void text_stroke(const ImVec2& pos, const ImColor& color, const std::string& text);

	/**
	 * @brief
	 */
	static void line(const ImVec2& from, const ImVec2& to, const ImColor& color);

	/**
	 * @brief
	 */
	static void line_stroke(ImVec2 from, ImVec2 to, ImColor color);

	/**
	 * @brief
	 */
	static void rect(const ImVec2 pos, const ImVec2 length, const ImColor color);

	/**
	 * @brief
	 */
	static void circle(const ImVec2& pos, const float& radius, const ImColor& color);

	/**
	 * @brief Render a single frame
	 */
	void frame();
}

#endif
