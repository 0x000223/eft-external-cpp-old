#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class cc_sharpen
{
	// CC_Sharpen
	
	uintptr_t address;

public:

	explicit cc_sharpen(const uintptr_t addr) : address(addr) {  }

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto set_strength(const float value) const -> void
	{
		return memory_handler::write(
			address + offset::cc_sharpen::strength, value);
	}

	auto set_clamp(const float value) const -> void
	{
		return memory_handler::write(
			address + offset::cc_sharpen::clamp, value);
	}
};