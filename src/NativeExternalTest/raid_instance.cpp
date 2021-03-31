#include "raid_instance.hpp"

std::shared_ptr<game_object>				raid_instance::attached_game_object = nullptr;
std::vector<std::shared_ptr<component>>		raid_instance::attached_components	= std::vector<std::shared_ptr<component>>();
uintptr_t									raid_instance::scripting_class		= 0;

auto raid_instance::init() -> void
{
	attached_game_object = game_object::find("GameWorld");

	attached_components = attached_game_object->get_all_components();

	scripting_class = attached_game_object->get_component_by_name("LocalGameWorld")->scripting_class;
}

auto raid_instance::release() -> void
{
		
}
