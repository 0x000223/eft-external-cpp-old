#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "managers.hpp"

#pragma warning (disable : 26451)

#ifndef SCRIPTING_HPP
#define SCRIPTING_HPP

struct scripting
{

	static auto type_to_scripting_type(const uintptr_t unity_type)
	{
		// Get scripting manager
		auto scripting_manager = managers::scripting_manager; // TODO - implement get_scripting_manager() in managers struct

		auto type_array = 
			memory_handler::read<uintptr_t>(scripting_manager + 0x2A); // Some type array

		auto unity_type_index = 
			memory_handler::read<uint32_t>(unity_type + 0x30);

		return memory_handler::read<uintptr_t>(type_array + 0x8 * unity_type_index);
	}
};

#endif