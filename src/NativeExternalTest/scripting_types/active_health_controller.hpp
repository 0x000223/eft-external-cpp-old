#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "health_controller.hpp"

class active_health_controller : public health_controller
{
	// E694
	
public:

	explicit active_health_controller(const uintptr_t addr) : health_controller(addr)
	{
		
	}

};