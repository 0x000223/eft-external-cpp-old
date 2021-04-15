#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class player_physical
{
	// E20C
	
	uintptr_t address;

	uintptr_t stamina_address;

	uintptr_t hands_stamina_address;

	uintptr_t oxygen_address;
	
public:

	explicit player_physical(const uintptr_t addr) : address(addr)
	{
		auto temp = 
			memory_handler::read<uintptr_t>(addr + offset::player::physical::stamina);

		stamina_address = temp + 0x48; // Current value

		temp =
			memory_handler::read<uintptr_t>(addr + offset::player::physical::hands_stamina);

		hands_stamina_address = temp + 0x48;

		temp =
			memory_handler::read<uintptr_t>(addr + offset::player::physical::oxygen);

		oxygen_address = temp + 0x48;
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto set_stamina(const float value) const -> void
	{
		memory_handler::write<float>(stamina_address, value);
	}

	auto set_hands_stamina(const float value) const -> void
	{
		memory_handler::write<float>(hands_stamina_address, value);
	}

	auto set_oxygen(const float value) const -> void
	{
		memory_handler::write<float>(oxygen_address, value);
	}
};