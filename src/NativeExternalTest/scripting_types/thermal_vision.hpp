#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class thermal_vision
{
	// ThermalVision
	
	uintptr_t address;
	
public:

	explicit thermal_vision(const uintptr_t addr) : address(addr) {  }

	auto get_address() const -> uintptr_t
	{
		return address;
	}
	
	auto toggle(const bool value) const -> void
	{
		return memory_handler::write(
			address + offset::thermal_vision::is_on, value);
	}
	
	auto enable() const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_on, true);
	}

	auto disable() const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_on, false);
	}

	auto is_noisy(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_noisy, value);
	}

	auto is_fps_stuck(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_fps_stuck, value);
	}

	auto is_motion_blurred(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_motion_blurred, value);
	}

	auto is_glitch(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_glitch, value);
	}

	auto is_pixelated(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::thermal_vision::is_pixelated, value);
	}
};