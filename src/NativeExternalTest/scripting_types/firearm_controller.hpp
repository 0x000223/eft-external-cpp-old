#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "shot.hpp"

class firearm_controller
{
	// FirearmController
	
	uintptr_t address;
	
public:

	std::shared_ptr<transform> fireport;

	float weapon_length;
	
	explicit firearm_controller(const uintptr_t addr) : address(addr)
	{
		auto fireport_bifacial = 
			memory_handler::read<uintptr_t>(
				address + offset::firearm_controller::fireport);

		fireport = 
			std::make_shared<transform>(
				memory_handler::read<uintptr_t>(
					fireport_bifacial + 0x10));

		weapon_length = 
			memory_handler::read<float>(
				address + offset::firearm_controller::weapon_length);
	}

	auto get_address() const -> uintptr_t 
	{
		return address;
	}

	auto set_weapon_length(const float value) const -> void
	{
		return memory_handler::write<float>(
			address + offset::firearm_controller::weapon_length, value);
	}

	auto is_aiming() const -> bool
	{
		return memory_handler::read<bool>(
			address + offset::firearm_controller::is_aiming);
	}

	auto get_shot_list() const -> std::vector<shot>
	{
		auto const list_address = 
			memory_handler::read<uintptr_t>(address + offset::firearm_controller::shot_list);
		
		return generic_list<shot>( list_address ).data;
	}
};