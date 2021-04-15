#pragma once
#include <string>

#include "scripts.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

struct menu
{
	static bool show_menu;
	
	static auto menu_style_default() -> void;

	static auto main_window() -> void;

	static auto visuals_tab_window() -> void;

	static auto aim_tab_window() -> void;

	static auto data_tab_window() -> void;
	
	struct settings
	{
		static float float_player_distance;

		static bool player_name;

		static bool player_health;
		
		static bool player_faction;
		
		static bool player_distance;
		
		static bool player_box;

		static bool player_snapline;

		static bool player_bones;
	};
};