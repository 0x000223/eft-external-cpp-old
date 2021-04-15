#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class character_controller_spawner
{
	// CharacterControllerSpawner

	uintptr_t address;
	
public:

	explicit character_controller_spawner(const uintptr_t addr) : address(addr)
	{
		
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_height() const -> float
	{
		return memory_handler::read<float>(
			address + offset::scripting::character_controller_spawner::height);
	}
};