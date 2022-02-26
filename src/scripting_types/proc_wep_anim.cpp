#include "proc_wep_anim.hpp"

void proc_wep_anim::set_mask(const int value) const {
	memory::write<int>(m_mask_address + 0x10, value);
}

void proc_wep_anim::set_shot_effector(const vector2 value, const float intensity) const {
	memory::write<vector2>(m_shot_effector_address + O_SHOTEFFECTOR_RECOILSTRENGTH_XY, value);
	memory::write<vector2>(m_shot_effector_address + O_SHOTEFFECTOR_RECOILSTRENGTH_Z, value);
	memory::write<float>(m_shot_effector_address + O_SHOTEFFECTOR_INTENSITY, intensity);
}

void proc_wep_anim::set_breath_effector(const float value) const {
	memory::write<float>(m_breath_effector_address + O_BREATHEFFECTOR_INTENSITY, value);
	memory::write<float>(m_breath_effector_address + O_BREATHEFFECTOR_BREATHINTENSITY, value);
}

void proc_wep_anim::set_walk_effector(const float value) const {
	memory::write<float>(m_walk_effector_address + O_WALKEFFECTOR_INTENSITY, value);
}

void proc_wep_anim::set_motion_effector(const float value) const {
	memory::write(m_motion_effector_address + O_MOTIONEFFECTOR_INTENSITY, value);
}

void proc_wep_anim::set_force_effector(const float value) const {
	memory::write<float>(m_force_effector_address + O_FORCEEFFECTOR_INTENSITY, value);
}
