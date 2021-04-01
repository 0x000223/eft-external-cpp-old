#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class thermal_vision
{
	uintptr_t address;
	
public:

	explicit thermal_vision(const uintptr_t addr) : address(addr) {  }

	auto toggle(const bool value) const -> void
	{
		return memory_handler::write(
			address + offset::scripting::ThermalVision::is_on, value);
	}
	
	auto enable() const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_on, true);
	}

	auto disable() const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_on, false);
	}

	auto is_noisy(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_noisy, value);
	}

	auto is_fps_stuck(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_fps_stuck, value);
	}

	auto is_motion_blurred(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_motion_blurred, value);
	}

	auto is_glitch(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_glitch, value);
	}

	auto is_pixelated(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::ThermalVision::is_pixelated, value);
	}
};