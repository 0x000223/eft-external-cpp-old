#pragma once
#include <memory>
#include <mutex>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "game_object.hpp"
#include "generic_list.hpp"
#include "eft_player.hpp"

class camera;

struct raid_instance
{
private:

	static uintptr_t scripting_class;
	
public:
	
	static std::unique_ptr<game_object> attached_game_object;

	static std::vector<component> attached_components;
	
	static std::shared_ptr<camera> main_camera_component;
	
	static std::shared_ptr<player> local_player;

	static std::vector<player> players;

	
	static auto init() -> BOOL;

	static auto release() -> void;

	static auto get_registered_players() -> std::vector<player>;

	static auto get_local_player() -> player*;

	static auto update_instance() -> void;

	static auto update_players() -> void;
};