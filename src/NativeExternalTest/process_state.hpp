#pragma once
#include <Windows.h>

#include "memory_handler.hpp"
#include "utility.hpp"

#ifndef STATE_HPP
#define STATE_HPP

struct process_state
{
	static DWORD process_id;

	static uintptr_t module_address;
	
	static bool heartbeat;

	static bool in_raid;

	static auto init() -> BOOL;

	static auto release() -> void;

	static auto get_process_id(std::string process_name) -> DWORD;

	static auto get_module_address(std::string module_name) -> uintptr_t;

	static auto is_heartbeat() -> bool;

	static auto is_in_raid() -> BOOL;
};

#endif