#include "process_state.hpp"
#include "game_object.hpp"

DWORD		process_state::process_id		= 0;
uintptr_t	process_state::module_address	= 0;
bool		process_state::heartbeat		= false;
bool		process_state::in_raid			= false;

auto process_state::init() -> BOOL
{
	process_id = get_process_id("EscapeFromTarkov");

	if (!process_id)
	{
		return FALSE;
	}

	memory_handler::attach(process_id);
	
	module_address = get_module_address("UnityPlayer.dll");

	if (!module_address)
	{
		return FALSE;
	}

	return TRUE;
}

auto process_state::release() -> void
{
	process_id = 0;

	module_address = 0;

	heartbeat = false;

	in_raid = false;
}

auto process_state::get_process_id(std::string process_name) -> DWORD
{
	std::wstring wide_process_name(process_name.begin(), process_name.end());

	return utility::get_process_id(wide_process_name);
}

auto process_state::get_module_address(std::string module_name) -> uintptr_t
{
	std::wstring wide_module_name(module_name.begin(), module_name.end());

	return memory_handler::get_module_address(wide_module_name.data());
}

auto process_state::is_heartbeat() -> bool
{
	return get_process_id("EscapeFromTarkov") != NULL;
}

auto process_state::is_in_raid() -> bool
{
	in_raid = game_object::find("GameWorld") != nullptr;

	return in_raid;
}