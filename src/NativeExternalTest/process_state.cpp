#include "process_state.hpp"
#include "game_object.hpp"
#include "raid_instance.hpp"
#include "scripts.hpp"

DWORD		process_state::process_id		= 0;
uintptr_t	process_state::module_address	= 0;
bool		process_state::is_heartbeat		= false;
bool		process_state::is_in_raid		= false;

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

	is_heartbeat = true;
	
	return TRUE;
}

auto process_state::release() -> void
{
	process_id		= 0;
	module_address	= 0;
	is_heartbeat	= false;
	is_in_raid		= false;
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

auto process_state::check_heartbeat() -> bool
{
	return get_process_id("EscapeFromTarkov") != NULL;
}

auto process_state::check_in_raid() -> bool
{
	return game_object::find("GameWorld");
}

auto process_state::process_state_monitor() -> void
{
	// Runs on a separate thread 
	// monitors process state (heartbeat / raid status) & updates state flags

	std::thread instance_updater; // TODO
	
	while(true)
	{
		Sleep(1000);

		if(!check_heartbeat() || (check_heartbeat() && !is_heartbeat))
		{
			// Capture if process not running OR just launched
			
			if(is_heartbeat)
			{
				raid_instance::release();

				managers::release();
				
				release();
			}
			else
			{
				// !is_heartbeat => requries initialization
				
				if(init())
				{
					managers::init();		
				}
			}
			
			continue;
		}

		if(!check_in_raid() || (check_in_raid() && !is_in_raid))
		{
			// Capture not in raid OR just got into a raid
			
			if(is_in_raid)
			{
				// Release raid instance resources

				raid_instance::release();

				is_in_raid = false;
			}
			else
			{
				// !is_in_raid => requires initialization

				if(raid_instance::init())
				{
					is_in_raid = true;

					scripts::reset();
					
					instance_updater = std::thread( raid_instance::update_instance );
					instance_updater.detach();
				}
			}
		}
	}
}