#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "EFT.Profile.hpp"

class player
{
	uintptr_t address;
	
public:

	std::shared_ptr<player_profile> profile;
	
	explicit player(const uintptr_t addr) : address(addr)
	{
		profile = 
			std::make_shared<player_profile>(
				memory_handler::read<uintptr_t>(addr + offset::player::player_profile));

	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}
};