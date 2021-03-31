#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"

class NightVision
{
	uintptr_t address;

public:

	explicit NightVision(const uintptr_t addr) : address(addr) {  }
	
	auto toggle(const bool value) const -> void
	{
		return memory_handler::write<bool>(
			address + offset::scripting::NightVision::is_on, value);
	}
};