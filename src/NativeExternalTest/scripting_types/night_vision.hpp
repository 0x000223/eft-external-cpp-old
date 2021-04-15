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
};