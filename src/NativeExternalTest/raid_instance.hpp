#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "game_object.hpp"

struct raid_instance
{
	static std::shared_ptr<game_object> attached_game_object;

	static std::vector<std::shared_ptr<component>> attached_components;
	
	static uintptr_t scripting_class;

	static std::shared_ptr<game_object> main_camera_game_object;
	
	// Player list

	// Loot list

	// Corpse list

	// Exfils

	
	static auto init() -> BOOL;

	static auto release() -> void;


	
private:

	
};