#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "settings.hpp"

#include "camera.hpp"
#include "thermal_vision.hpp"
#include "night_vision.hpp"
#include "visor_effect.hpp"
#include "raid_instance.hpp"
#include "material.hpp"
#include "time_manager.hpp"

struct scripts
{
	static auto run_scripts() -> void;

	static auto reset() -> void;
	
	static auto toggle_thermal_vision() -> void;

	static auto toggle_night_vision() -> void;

	static auto nvg_set_red(const float value) -> void;
	
	static auto nvg_set_green(const float value) -> void;

	static auto nvg_set_blue(const float value) -> void;
	
	static auto toggle_no_visor() -> void;
	
	static auto unlimited_stamina() -> void;

	static auto no_recoil() -> void;

	static auto fov_aim() -> void;
	
	static auto find_closest_target() -> player;

	static auto test() -> void;
};