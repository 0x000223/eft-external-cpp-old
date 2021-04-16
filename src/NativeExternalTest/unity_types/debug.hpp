#pragma once

#include "memory_handler.hpp"
#include "offset.hpp"
#include "unity.hpp"

struct debug
{
	static auto is_debug_build()
	{
		auto debug_class = unity::find_type_by_name("Debug");

		// TODO
	}
};