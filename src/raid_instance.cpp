#include "raid_instance.hpp"
#include "camera.hpp"

std::mutex mtx;

std::unique_ptr<game_object>	raid_instance::attached_game_object		= nullptr;
std::shared_ptr<camera>			raid_instance::main_camera_component	= nullptr;
std::shared_ptr<player>			raid_instance::local_player				= nullptr;
std::vector<player>				raid_instance::players					= std::vector<player>();
std::vector<component>			raid_instance::attached_components		= std::vector<component>();
uintptr_t						raid_instance::scripting_class			= 0;

auto raid_instance::init() -> BOOL
{
	attached_game_object = std::unique_ptr<game_object>( game_object::find("GameWorld") );
	
	if(!attached_game_object)
	{
		return FALSE;
	}

	attached_components = attached_game_object->get_all_components();

	if(attached_components.size() != attached_game_object->component_count)
	{
		return FALSE;
	}
	
	main_camera_component = std::shared_ptr<camera>( camera::get_main_camera() );
	
	if(!main_camera_component)
	{
		return FALSE;
	}

	auto local_game_world = attached_game_object->get_component_by_name("GameWorld");

	if(!local_game_world)
	{
		// When local game world being initialized some objects may init with a delay
		// so we have to restart few times
		
		return FALSE;
	}

	scripting_class = local_game_world.scripting_class;
	
	local_player = std::shared_ptr<player>( get_local_player() );

	if(!local_player)
	{
		return FALSE;
	}

	players = get_registered_players();

	if(players.empty())
	{
		return FALSE;
	}
	
	return TRUE;
}

auto raid_instance::release() -> void
{
	scripting_class = 0;
}

auto raid_instance::get_registered_players() -> std::vector<player>
{
	if(!process_state::check_in_raid())
	{
		return std::vector<player>();
	}
	
	auto ret_list = std::vector<player>();

	auto list_address = 
		memory_handler::read<uintptr_t>(
			scripting_class + offset::game_world::registered_players);

	auto count = 
		memory_handler::read<uint32_t>(
			list_address + offset::generic_list::count);

	auto base =
		memory_handler::read<uintptr_t>(
			list_address + offset::generic_list::base) + offset::array::base;

	for(unsigned index = 0; index < count; ++index)
	{
		auto temp = memory_handler::read<uintptr_t>(base + index * 8);

		ret_list.emplace_back(temp);
	}
	
	return ret_list;
}

auto raid_instance::get_local_player() -> player*
{
	std::vector<player> list = get_registered_players();

	if(list.empty())
	{
		return nullptr;
	}

	return new player { list[0].get_address() };
}

auto raid_instance::update_instance() -> void
{
	// Runs on a separate thread

	while(process_state::is_in_raid)
	{
		Sleep(1000);

		update_players();
	}
}

auto raid_instance::update_players() -> void
{
	auto new_list = get_registered_players();

	if(new_list != players)
	{
		mtx.lock();
		
		players.swap(new_list);

		mtx.unlock();
	}

	new_list.clear();
}