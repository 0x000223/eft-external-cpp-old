#include "raid_instance.hpp"

std::shared_ptr<game_object>				raid_instance::attached_game_object		= nullptr;
std::shared_ptr<game_object>				raid_instance::main_camera_game_object	= nullptr;
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
	
	main_camera_game_object = game_object::find_with_tag(5);
	
	if(!main_camera_game_object)
	{
		return FALSE;
	}
	
	return TRUE;
}

auto raid_instance::release() -> void
{
	attached_game_object->reset();

	for(auto& component : attached_components)
	{
		component.reset();
	}

	scripting_class = 0;

	main_camera_game_object->reset();
}
