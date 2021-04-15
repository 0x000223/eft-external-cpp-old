#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "health.hpp"

class body_part_state
{
	// BodyPartState

	uintptr_t address;
	
public:

	std::shared_ptr<health> health;

	body_part_state() = default;
	
	explicit body_part_state(const uintptr_t addr) : address(addr)
	{
		auto health_address = 
			memory_handler::read<uintptr_t>(address + offset::bodypartstate::health_struct);
		
		health = std::make_shared<class health>( health_address );
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto is_destroyed() const -> bool
	{
		return memory_handler::read<bool>(
			address + offset::bodypartstate::is_destroyed);
	}

	auto get_body_part_health() const -> float
	{
		return health->get_current();
	}

	auto get_body_part_max_health() const -> float
	{
		return health->get_maximum();
	}
};