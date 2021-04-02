#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "utility.hpp"
#include "transform.hpp"
#include "eft_profile.hpp"
#include "player_physical.hpp"
#include "eft_player_body.hpp"

class player
{
	// EFT.Player
	
	uintptr_t address;
	
public:

	bool is_local;
	
	std::shared_ptr<player_profile> profile;

	std::shared_ptr<player_physical> physical;

	std::shared_ptr<player_body> body;
	
	std::string name;
	
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

		body =
			std::make_shared<player_body>(
				memory_handler::read<uintptr_t>(addr + offset::player::player_body));

		
		name = utility::wide_to_narrow(profile->get_nickname());
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	bool operator ! () const
	{
		return !this->address;
	}
	
	bool operator == (player& other) const
	{
		return this->address == other.address;
	}

	bool operator != (player& other) const
	{
		return this->address != other.address;
	}
};