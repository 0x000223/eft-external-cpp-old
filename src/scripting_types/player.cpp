#include "player.hpp"

float player::get_health() const {
	return health_controller->get_player_health();
}

float player::get_max_health() const {
	return health_controller->get_player_max_health();
}

vector3 player::get_root_position() const { 
	return body->bones->root.get_position();
}

vector3 player::get_head_position() const {
	return body->bones->head.get_position();
}
