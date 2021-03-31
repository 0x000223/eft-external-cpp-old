#include "managers.hpp"

uintptr_t managers::context				= 0;
uintptr_t managers::type_manager		= 0;
uintptr_t managers::game_object_manager	= 0;
uintptr_t managers::render_manager		= 0;
uintptr_t managers::scripting_manager	= 0;

auto managers::init() -> BOOL
{
	context = get_context();

	if(!context)
	{
		return FALSE;
	}
	
	game_object_manager = get_object_manager();

	if (!game_object_manager)
	{
		return FALSE;
	}

	render_manager = get_render_manager();

	if (!render_manager)
	{
		return FALSE;
	}

	type_manager = get_type_manager();

	if(!type_manager)
	{
		return FALSE;
	}

	scripting_manager = get_scripting_manager();

	if(!scripting_manager)
	{
		return FALSE;
	}
	
	return TRUE;
}

auto managers::release() -> void
{
	game_object_manager = 0;

	render_manager = 0;

	type_manager = 0;
	
	scripting_manager = 0;
}

auto managers::get_context() -> uintptr_t
{
	if(!process_state::module_address)
	{
		return 0;
	}

	return memory_handler::read<uintptr_t>(
		process_state::module_address + offset::global::manager_context);
}

auto managers::get_manager_from_context(const int index) -> uintptr_t
{
	return memory_handler::read<uintptr_t>(context + 0x8 * index);
}

auto managers::get_type_manager() -> uintptr_t
{
	if(!process_state::module_address)
	{
		return 0;
	}

	return memory_handler::read<uintptr_t>(
		process_state::module_address + offset::global::type_manager);
}

auto managers::get_object_manager() -> uintptr_t
{
	if (!process_state::module_address)
	{
		return 0;
	}

	return memory_handler::read<uintptr_t>(
		process_state::module_address + offset::global::object_manager);
}

auto managers::get_render_manager() -> uintptr_t
{
	if (!process_state::module_address)
	{
		return 0;
	}

	return memory_handler::read<uintptr_t>(
		process_state::module_address + offset::global::render_manager);
}

auto managers::get_network_manager() -> uintptr_t
{
	if (!process_state::module_address)
	{
		return 0;
	}

	return memory_handler::read<uintptr_t>(
		process_state::module_address + offset::global::network_manager);
}

auto managers::get_scripting_manager() -> uintptr_t
{
	return get_manager_from_context(5);
}
