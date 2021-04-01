#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "eft_profile.hpp"
#include "player_physical.hpp"

class player
{
	uintptr_t address;
	
public:

	bool is_local;
	
	std::shared_ptr<player_profile> profile;

	std::shared_ptr<player_physical> physical;

	std::wstring name;
	
	explicit player(const uintptr_t addr) : address(addr)
	{
		is_local =
			memory_handler::read<bool>(addr + offset::player::is_local);
		
		profile = 
			std::make_shared<player_profile>(
				memory_handler::read<uintptr_t>(addr + offset::player::player_profile));

		physical =
			std::make_shared<player_physical>(
				memory_handler::read<uintptr_t>(
					addr + offset::player::player_physical));
		
		name = profile->get_nickname();
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}
};