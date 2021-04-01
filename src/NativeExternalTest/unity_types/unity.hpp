#pragma once
#include <cstdint>
#include <map>

#include "memory_handler.hpp"
#include "managers.hpp"

#pragma warning (disable : 26451)

class unity
{
	// TODO
	// FindTypeByPersistentTypeID(int)
	
public:

	static auto get_registered_types() -> std::map<std::string, uintptr_t>
	{
		if(!managers::type_manager)
		{
			return std::map<std::string, uintptr_t>();
		}
		
		auto array_base = 
			memory_handler::read<uintptr_t>(managers::type_manager + 0x18);

		auto count = 
			memory_handler::read<uint32_t>(managers::type_manager + 0x20);

		auto last_entry = 
			array_base + count + ( 2 * (0xC + count));

		std::map<std::string, uintptr_t> registered_types;

		while(array_base < last_entry)
		{
			if(memory_handler::read<uint32_t>(array_base) < 0xFFFFFFFE)
			{
				auto name_address = 
					memory_handler::read<uintptr_t>(array_base + 0x8);
				
				auto type_name = 
					memory_handler::read_narrow_string(name_address);
				
				auto type_address = 
					memory_handler::read<uintptr_t>(array_base + 0x10);

				registered_types[type_name] = type_address;
			}

			array_base += 0x18;
		}

		return registered_types;
	}

	static auto find_type_by_name(const std::string target_type_name) -> uintptr_t
	{
		if(!managers::type_manager)
		{
			return 0;
		}
		
		auto array_base = 
			memory_handler::read<uintptr_t>(managers::type_manager + 0x18);
		
		auto count = 
			memory_handler::read<uint32_t>(managers::type_manager + 0x20);

		auto last_entry = 
			array_base + count + (2 * ( 0xC + count ));

		while(array_base < last_entry)
		{
			if(memory_handler::read<uint32_t>(array_base) < 0xFFFFFFFE)
			{
				auto name_address = 
					memory_handler::read<uintptr_t>(array_base + 0x8);
				
				auto type_name = 
					memory_handler::read_narrow_string(name_address);

				if(type_name == target_type_name)
				{
					return memory_handler::read<uintptr_t>(array_base + 0x10);
				}
			}

			array_base += 0x18;
		}

		return 0;
	}

	static auto find_all_derived_types(uintptr_t unity_type) -> std::vector<uintptr_t> // TODO - return std::map<std::string, uintptr_t>
	{
		if(!managers::type_manager)
		{
			return std::vector<uintptr_t>();
		}

		auto derived_count = memory_handler::read<uint32_t>(unity_type + 0x34);
		auto type_index = memory_handler::read<uint32_t>(unity_type + 0x30);

		auto total = type_index + derived_count;

		std::vector<uintptr_t> derived_types;
		
		if(type_index < total)
		{
			auto type_list = 
					memory_handler::read<uintptr_t>(managers::type_manager);
			
			auto start_index = 8 * type_index;

			do
			{
				auto derived_type = 
					memory_handler::read<uintptr_t>(type_list + start_index + 0x8);

				derived_types.push_back(derived_type);
				
				start_index += 0x8;

				derived_count--;
				
			} while( derived_count );
		}

		return derived_types;
	}
};