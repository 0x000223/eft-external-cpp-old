#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "managers.hpp"

class time_manager
{
	// Internal structure

private:


public:

	static auto get_time_manager() -> uintptr_t
	{
		if(!managers::context)
		{
			return 0;
		}
		
		return managers::get_manager_from_context(7);
	}

	static auto get_time_scale() -> float
	{
		auto const time_manager = get_time_manager();

		return memory_handler::read<float>(time_manager + offset::time_manager::time_scale);
	}

	static auto set_time_scale(const float value) -> void
	{
		auto const time_manager = get_time_manager();

		if(!time_manager)
		{
			return;
		}

		return memory_handler::write<float>(time_manager + offset::time_manager::time_scale, value);
	}
};