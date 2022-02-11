#pragma once
#include <vector>
#include <string>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "system_string.hpp"

#pragma warning (disable : 26451)

class skeleton
{
	// Diz.Skinning.Skeleton

	uintptr_t address;

	std::vector<std::wstring> keys;

	std::vector<transform> values;
	
	auto parse_keys() const -> std::vector<std::wstring>
	{
		auto keys_address = 
			memory_handler::read<uintptr_t>(
				address + offset::skeleton::keys);

		auto count = 
			memory_handler::read<uint32_t>(
				keys_address + offset::generic_list::count);

		if(count > 138)
		{
			return std::vector<std::wstring>();
		}
		
		auto base =
			memory_handler::read<uintptr_t>(
				keys_address + offset::generic_list::base) + offset::array::base;

		std::vector<std::wstring> ret_keys;

		for(unsigned index = 0; index < count; index++)
		{
			auto result = memory_handler::read_wide_string( base + index * 8 );

			if(result.empty())
			{
				continue;
			}
			
			ret_keys.push_back( result );
		}

		return ret_keys;
	}

	auto parse_values() const -> std::vector<transform>
	{
		auto values_address =
			memory_handler::read<uintptr_t>(
				address + offset::skeleton::values);

		auto count =
			memory_handler::read<uint32_t>(
				values_address + offset::generic_list::count);

		if(count > 138)
		{
			return std::vector<transform>(); // TODO - temp bandaid solution
		}
		
		auto base =
			memory_handler::read<uintptr_t>(
				values_address + offset::generic_list::base) + offset::array::base;

		std::vector<transform> ret_transforms;
		
		for(unsigned index = 0; index < count; index++)
		{
			auto transform_address = memory_handler::read<uintptr_t>(base + index * 8);

			ret_transforms.emplace_back(transform_address);
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

	auto get_values() const -> std::vector<transform>
	{
		return values;
	}
};