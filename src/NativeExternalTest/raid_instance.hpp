#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "game_object.hpp"
#include "list_t.hpp"
#include "eft_player.hpp"

struct raid_instance
{
	static std::shared_ptr<game_object> attached_game_object;

	static std::vector<std::shared_ptr<component>> attached_components;
	
	static uintptr_t scripting_class;

	static std::shared_ptr<game_object> main_camera_game_object;

	static std::shared_ptr<player> local_player;
	
	// Player list

	// Loot list

	// Corpse list

	// Exfils
	
	static auto init() -> BOOL;

	static auto release() -> void;

	static auto get_registered_players() -> std::vector<player>;

	static auto get_local_player() -> std::shared_ptr<player>;

	// Thread - monitor registered players list
};