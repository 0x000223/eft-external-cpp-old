#include "world.hpp"
#include "math.hpp"
using namespace std;

mutex mtx;

bool world::is_active = false;

address_t world::scripting_object_address = 0;

game_object world::attached_game_object = game_object();

camera world::main_camera = camera();

player world::local_player = player();

vector<player> world::players = vector<player>();

bool world::check_if_active() {
	const auto camera = game_object::find_main_camera();
	if (camera.m_name == "") {
		return false;
	}
	return true;
}

void world::initialize() {

	auto camera_object = game_object::find_main_camera();

	while (camera_object.m_name == "") { // 'FPS Camera' GameObject may initialize with delay
		camera_object = game_object::find_main_camera();
	}

	world::main_camera = camera(camera_object.get_component_by_name("Camera").get_address());

	world::attached_game_object = game_object::find("GameWorld");

	while (world::attached_game_object.m_name == "") { // GameWorld GameObject may initialize with delay
		world::attached_game_object = game_object::find("GameWorld");
	}

	component& game_world_component = world::attached_game_object.get_component_by_name("GameWorld");

	while (game_world_component.get_address() == 0) { // GameWorld Component may initialize with delay
		game_world_component = world::attached_game_object.get_component_by_name("GameWorld");
	}

	world::scripting_object_address = game_world_component.m_scripting_object_address;

	world::local_player = world::get_local_player();
}

void world::terminate() {
	world::attached_game_object = game_object();
	world::scripting_object_address = 0;
	world::main_camera = camera();
	world::players = vector<player>();
	world::local_player = player();
}

vector<player> world::get_player_list() {
	if (scripting_object_address == 0) {
		return vector<player>();
	}
	return utility::parse_list<player>(scripting_object_address + O_GAMEWORLD_REGISTEREDPLAYERS);
}

player world::get_local_player() {
	const auto player_list = get_player_list();
	if (player_list.empty()) {
		return player();
	}
	return player_list[0]; // First entry is local player
}

void world::update_state() {

	const auto active = check_if_active();
	if (active != world::is_active) { // State has changed

		// Detect whether GameWorld was activated/deactivated

		if (active == true) { // GameWorld has been activated - need to initialize
			initialize();
		}
		else { // GameWorld has been deactivated - need to cleanup
			terminate();
		}
	}
	is_active = active;
}

void world::update_players() {

	if (world::is_active) {
		auto new_player_list = get_player_list();

		if (new_player_list.size() != players.size()) { // Different count - need to sync
			world::players.swap(new_player_list);
		}
	}
}