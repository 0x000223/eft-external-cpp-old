#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "managers.hpp"

class persistent_manager
{
	// Unity internal type
	
private:

public:


	static auto read_object(const int instance_id) -> void
	{
		if(!managers::persistent_manager)
		{
			return;
		}

		auto v1 = memory_handler::read<uintptr_t>(managers::persistent_manager + 0x13);

		// Lookup an integer from internal hash_set
		
		auto v3 = memory_handler::read<uint32_t>(v1 + 0x2);

		auto v4 = memory_handler::read<uintptr_t>(v1);

		auto v5 = (0x21 * ((0x1001 * instance_id + 0x7ED55D16) ^ ((unsigned int)(0x1001 * instance_id + 0x7ED55D16) >> 0x13) ^ 0xC761C23C) + 0x165667B1) << 0x9;

		// TODO - finish this mess
	}
};