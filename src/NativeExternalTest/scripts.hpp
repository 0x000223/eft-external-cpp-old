#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"

#include "camera.hpp"
#include "thermal_vision.hpp"
#include "night_vision.hpp"
#include "raid_instance.hpp"

#ifndef SCRIPTS_HPP
#define SCRIPTS_HPP

struct scripts
{
	struct flags
	{
		static bool thermal_vision;

		static bool night_vision;

		static bool no_recoil;

		static bool unlimited_stamina;
	};
	
	static auto run_scripts() -> void;

	static auto reset() -> void; // Reset script flags upon entering new instance
	
	static auto toggle_thermal_vision() -> void;

	static auto toggle_night_vision() -> void;

	static auto unlimited_stamina() -> void;
};

#endif