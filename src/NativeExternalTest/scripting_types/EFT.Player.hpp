#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class player
{
	uintptr_t address;
	
public:

	explicit player(const uintptr_t addr) : address(addr)
	{
		
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	
};