#include "player.hpp"

float player::get_health() {
	//return health_controller->get_player_health();
	return 0.f;
}

float player::get_max_health() {
	//return health_controller->get_player_max_health();
	return 0.f;
}

vector3 player::get_root_position() { 
	return m_playerbody.m_positions[BoneEnum::Root];
}

vector3 player::get_head_position() {
	return m_playerbody.m_positions[BoneEnum::Head];
}

vector2 player::get_rotation() const {
	return memory::read<vector2>(movement_context_address + O_MOVEMENTCONTEXT_ROTATION);
}

void player::set_rotation(const vector2 rotation) const {
	return memory::write<vector2>(movement_context_address + O_MOVEMENTCONTEXT_ROTATION, rotation);
}

transform player::get_fireport() {
	
	const auto fireport_bifacial = memory::read<address_t>(hands_controller_address + O_FIREARMCONTROLLER_FIREPORT);
	const auto scripting_transform = memory::read<address_t>(fireport_bifacial + O_BIFACIALTRANSFORM_ORIGINAL);
	const auto transform_address = memory::read<address_t>(scripting_transform + 0x10); // Scrpiting transform to UnityEngine::Transform

	if (transform_address == 0) {
		return transform();
	}

	return transform(transform_address);
}

void player::fill_stamina(const float value) const {
	m_physical.set_legs_stamina(300);
	m_physical.set_hands_stamina(300);
	m_physical.set_oxygen(300);
}
