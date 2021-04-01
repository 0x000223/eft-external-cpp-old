#pragma once
#include <thread>
#include <Windows.h>

#include "utility.hpp"
#include "memory_handler.hpp"

struct process_state
{
	static DWORD process_id;

	static uintptr_t module_address;
	
	static bool is_heartbeat;

	static bool is_in_raid;

	static auto init() -> BOOL;

	static auto release() -> void;

	static auto get_process_id(std::string process_name) -> DWORD;

	static auto get_module_address(std::string module_name) -> uintptr_t;

	static auto check_heartbeat() -> bool;

	static auto check_in_raid() -> bool;

	static auto process_state_monitor() -> void;
};