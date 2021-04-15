#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class ballistics_calculator
{
	// EFT.Ballistics.BallisticsCalculator
	
	uintptr_t address;
	
public:

	explicit ballistics_calculator(const uintptr_t addr) : address(addr)
	{
		
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}
};