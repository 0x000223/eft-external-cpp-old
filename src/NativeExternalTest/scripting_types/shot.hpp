#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "utility.hpp"

class shot
{
	// E8D8

private:
	
	uintptr_t address;
	
public:

	shot() = default;
	
	explicit shot(const uintptr_t addr) : address(addr)
	{
		
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_current_position() const -> vector3
	{
		return memory_handler::read<vector3>(
			address + offset::shot::current_position);
	}

	auto set_current_position(const vector3 value) const -> void
	{
		return memory_handler::write<vector3>(
			address + offset::shot::current_position, value);
	}
};