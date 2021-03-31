#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"

#include "camera.hpp"
#include "ThermalVision.h"
#include "NightVision.h"

#ifndef SCRIPTS_HPP
#define SCRIPTS_HPP

struct scripts
{
	// Flags

	static bool thermal_vision;

	static bool night_vision;

	static bool no_recoil;
	
	static auto run_scripts() -> void;

	static auto reset() -> void; // Reset script flags upon entering new instance
	
	static auto toggle_thermal_vision() -> void;

	static auto toggle_night_vision() -> void;
};

#endif