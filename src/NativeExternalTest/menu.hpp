#pragma once
#include <string>

#include "graphics_handler.hpp"
#include "managers.hpp"
#include "game_object.hpp"
#include "camera.hpp"
#include "scripts.hpp"

#include "CC_BrightnessContrastGamma.hpp"
#include "ThermalVision.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#ifndef MENU_HPP
#define MENU_HPP

struct menu
{
	static bool show_menu;
	
	static auto set_menu_style() -> void;

	static auto main_menu_window() -> void;
};

#endif