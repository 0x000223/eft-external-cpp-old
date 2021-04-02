#include "raid_instance.hpp"
#include "camera.hpp"

std::shared_ptr<game_object>				raid_instance::attached_game_object		= nullptr;
std::shared_ptr<camera>					    raid_instance::main_camera_component	= nullptr;
std::shared_ptr<player>						raid_instance::local_player				= nullptr;
std::vector<player>							raid_instance::players					= std::vector<player>();
std::vector<std::shared_ptr<component>>		raid_instance::attached_components		= std::vector<std::shared_ptr<component>>();
uintptr_t									raid_instance::scripting_class			= 0;

auto raid_instance::init() -> BOOL
{
	attached_game_object = game_object::find("GameWorld");
	
	if(!attached_game_object)
	{
		return FALSE;
	}
	
	attached_components = attached_game_object->get_all_components();
	
	scripting_class = attached_game_object->get_component_by_name("LocalGameWorld")->scripting_class;
	
	if(!scripting_class)
	{
		return FALSE;
	}
	
	main_camera_component = camera::get_main_camera();
	
	if(!main_camera_component)
	{
		return FALSE;
	}
	
	local_player = get_local_player();

	players = get_registered_players();
	
	process_state::is_in_raid = true;
	
	return TRUE;
}

auto raid_instance::release() -> void
{
	attached_game_object.reset();

	for(auto& component : attached_components)
	{
		component.reset();
	}

	scripting_class = 0;

	main_camera_component.reset();
	
	local_player.reset();

	process_state::is_in_raid = false;
}

auto raid_instance::get_registered_players() -> std::vector<player>
{
	auto players = 
		generic_list<player>( memory_handler::read<uintptr_t>(scripting_class + offset::game_world::registered_players) );

	return players.data;
}

auto raid_instance::get_local_player() -> std::shared_ptr<player>
{
	auto players = get_registered_players();

	for(auto& object : players)
	{
		if(object.is_local)
		{
			return std::make_shared<player>(object);
		}
	}

	return nullptr;
}
