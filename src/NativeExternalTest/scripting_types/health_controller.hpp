#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "e_body_part.hpp"
#include "health.hpp"
#include "generic_dictionary.hpp"
#include "body_part_state.hpp"

class health_controller
{
	// E695

	uintptr_t address;
	
public:

	std::vector<body_part_state> body_parts;
	
	explicit health_controller(const uintptr_t addr) : address(addr)
	{
		auto dict_address = 
			memory_handler::read<uintptr_t>(
				address + offset::health_controller::body_parts_dictionary);

		for(auto parsed_dict = generic_dictionary<e_body_part, uintptr_t>( dict_address ); 
			auto& entry : parsed_dict.entries)
		{
			body_parts.emplace_back( entry.value );
		}
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_player_health() const -> float
	{
		auto ret = 0.f;

		for(const auto& entry : body_parts)
		{
			ret += entry.get_body_part_health();	
		}
		
		return ret;
	}

	auto get_player_max_health() const -> float
	{
		auto ret = 0.f;

		for(const auto& entry : body_parts)
		{
			ret += entry.get_body_part_max_health();
		}

		return ret;
	}
};