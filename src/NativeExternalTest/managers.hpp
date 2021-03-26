#pragma once
#include <cstdint>

#include "memory_handler.hpp"
#include "offset.hpp"
#include "process_state.hpp"

#ifndef MANAGERS_HPP
#define MANAGERS_HPP

struct managers // Aggregate unity managers
{
	static uintptr_t type_manager;
	
	static uintptr_t object_manager;

	static uintptr_t render_manager;

	static uintptr_t network_manager;

	static uintptr_t scripting_manager;
	
	static auto init() -> BOOL;

	static auto release() -> void;

	static auto get_type_manager() -> uintptr_t;
	
	static auto get_object_manager() -> uintptr_t;

	static auto get_render_manager() -> uintptr_t;

	static auto get_network_manager() -> uintptr_t;
};

#endif
