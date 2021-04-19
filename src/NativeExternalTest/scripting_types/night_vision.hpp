#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"

class night_vision
{
	uintptr_t address;

public:

	explicit night_vision(const uintptr_t addr) : address(addr) {  }
	
	auto toggle(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::night_vision::is_on, value);
	}

	auto get_color() const -> vector3
	{
		return memory_handler::read<vector3>(
			address + offset::night_vision::red);
	}

	auto set_red(const float value) const -> void
	{
		return memory_handler::write<float>(
			address + offset::night_vision::red, value);
	}

	auto set_green(const float value) const -> void
	{
		return memory_handler::write<float>(
			address + offset::night_vision::green, value);
	}

	auto set_blue(const float value) const -> void
	{
		return memory_handler::write<float>(
			address + offset::night_vision::blue, value);
	}
};