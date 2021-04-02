#pragma once
#include <vector>
#include <string>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "generic_list.hpp"
#include "system_string.hpp"

#pragma warning (disable : 26451)

class skeleton
{
	// Diz.Skinning.Skeleton

	uintptr_t address;

	std::vector<std::wstring> keys;

	std::vector<uintptr_t> values;
	
	auto parse_keys() const -> std::vector<std::wstring>
	{
		auto keys_address = 
			memory_handler::read<uintptr_t>(address + offset::scripting::skeleton::keys);

		auto count = 
			memory_handler::read<uint32_t>(keys_address + offset::generic_list::count);

		auto base =
			memory_handler::read<uintptr_t>(keys_address + offset::generic_list::base) + offset::array::base;

		std::vector<std::wstring> ret_keys;
		
		for(unsigned index = 0; index < count; index++)
		{
			ret_keys.push_back( memory_handler::read_wide_string( base + index * 8 ) );
		}

		return ret_keys;
	}

	auto parse_values() const -> std::vector<uintptr_t>
	{
		auto values_address =
			memory_handler::read<uintptr_t>(address + offset::scripting::skeleton::values);

		auto count =
			memory_handler::read<uint32_t>(values_address + offset::generic_list::count);

		auto base =
			memory_handler::read<uintptr_t>(values_address + offset::generic_list::base) + offset::array::base;

		std::vector<uintptr_t> ret_transforms;

		for(unsigned index = 0; index < count; index++)
		{
			auto transform_address = memory_handler::read<uintptr_t>(base + index * 8);

			ret_transforms.push_back( transform_address );
		}

		return ret_transforms;
	}
	
public:

	explicit skeleton(const uintptr_t addr) : address(addr)
	{
		keys = parse_keys();

		values = parse_values();
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_keys() const -> std::vector<std::wstring>
	{
		return keys;
	}

	auto get_values() const -> std::vector<uintptr_t>
	{
		return values;
	}
};