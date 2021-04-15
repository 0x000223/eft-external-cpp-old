#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "utility.hpp"

class movement_context
{
	// E4FE
	
private:

	uintptr_t address;

public:

	movement_context() = default;

	explicit movement_context(const uintptr_t addr) : address(addr){  }

	auto get_addrss() const -> uintptr_t
	{
		return address;
	}

	auto get_rotation() const -> vector2
	{
		return memory_handler::read<vector2>(
			address + offset::movement_context::rotation);	
	}

	auto set_rotation(const vector2 value) const -> void
	{
		return memory_handler::write<vector2>(
			address + offset::movement_context::rotation, value);
	}
};