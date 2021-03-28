#pragma once
#include <cstdint>

#include "memory_handler.hpp"
#include "offset.hpp"

#ifndef MANAGERS_HPP
#define MANAGERS_HPP

struct managers // Aggregate unity managers
{
	static uintptr_t context;
	
	static uintptr_t type_manager;
	
	static uintptr_t game_object_manager;

	static uintptr_t render_manager;

	static uintptr_t network_manager;

	static uintptr_t scripting_manager;
	
	static auto init() -> BOOL;

	static auto release() -> void;

	static auto get_context() -> uintptr_t;

	static auto get_manager_from_context(int index) -> uintptr_t;
	
	static auto get_type_manager() -> uintptr_t;
	
	static auto get_object_manager() -> uintptr_t;

	static auto get_render_manager() -> uintptr_t;

	static auto get_network_manager() -> uintptr_t;

	static auto get_scripting_manager() -> uintptr_t;
};

#endif
