#include "feature.hpp"

#include "player.hpp"
#include "render_backend.hpp"

#include <numbers>
using namespace std;

static player get_best_target() {
	
	auto best_distance = 10000.f;
	auto best_target = player(0);

	for (const auto& player : world::players) {
		if (player.get_address() == world::local_player.get_address()) { // Skip localplayer
			continue;
		}

		// Filter by aim distance setting

		/**
		 * For now AIMBOT will focus only on head bone
		 */
		const auto bone = world::main_camera.world_to_screen(player.m_playerbody.m_positions[BoneEnum::Head]);

		const auto distance = bone.distance(render_backend::get_window_center()); // Distance from screen center to target bone

		/**
		 * For now FOV will be hardcoded - later will be integrated into GUI setting
		 */
		if (distance < 90.f) {
			if (distance < best_distance) {
				best_distance = distance;
				best_target = player;
			}
		}
	}

	return best_target;
}

void feature::aimbot_fov() {

	auto fireport3 = world::local_player.get_fireport().get_position();
	if (fireport3 == vector3::zero) {
		return;
	}

	auto target = get_best_target();
	if (target.get_address() == 0) { // If empty object
		return;
	}

	auto new_rotation = vector3::calculate_angle(fireport3, target.get_head_position()); // Fireport => Target Head Position

	world::local_player.set_rotation(new_rotation);
}

void feature::no_recoil() {
	//world::local_player.m_proc_wep_anim.set_mask(1);
	world::local_player.m_proc_wep_anim.set_breath_effector(0);
	world::local_player.m_proc_wep_anim.set_walk_effector(0);
	world::local_player.m_proc_wep_anim.set_motion_effector(0);
	world::local_player.m_proc_wep_anim.set_force_effector(0);
	world::local_player.m_proc_wep_anim.set_shot_effector(vector2::zero, 0);

	memory::write<float>(world::local_player.m_proc_wep_anim.m_address + O_PROCWEPANIM_AIMINGDISPLACEMENT, 0);
}

void feature::thermal_vision() {
	
	static bool toggle = false;
	const auto camera_obj = game_object::find_main_camera();
	const auto thermal_comp = camera_obj.get_component_by_name("Thermal");
	memory::write<bool>(thermal_comp.m_scripting_object_address + O_THERMALVISION_ON, toggle);
	memory::write<bool>(thermal_comp.m_scripting_object_address + O_THERMALVISION_ISNOISY, false);
	memory::write<bool>(thermal_comp.m_scripting_object_address + O_THERMALVISION_ISMUTIONBLURRED, false);
	toggle = !toggle;
}

void feature::night_vision() {

	static bool toggle = false;
	const auto camera_obj = game_object::find_main_camera();
	const auto night_comp = camera_obj.get_component_by_name("Night");
	memory::write<bool>(night_comp.m_scripting_object_address + O_NIGHTVISION_ON, toggle);
	toggle = !toggle;
}
