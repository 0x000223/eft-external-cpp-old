#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class procedural_weapon_animation
{

	uintptr_t address;

	uintptr_t shot_effector;

	uintptr_t breath_effector;

	uintptr_t walk_effector;
	
public:

	explicit procedural_weapon_animation(const uintptr_t addr) : address(addr)
	{
		shot_effector =
			memory_handler::read<uintptr_t>(
				address + offset::procedural_weapon_animation::shot_effector);

		breath_effector =
			memory_handler::read<uintptr_t>(
				address + offset::procedural_weapon_animation::breath_effector);

		walk_effector =
			memory_handler::read<uintptr_t>(
				address + offset::procedural_weapon_animation::walk_effector);
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}
	
	auto set_mask(const int value) const -> void
	{
		return memory_handler::write<int>(
			address + offset::procedural_weapon_animation::mask, value);
	}

	auto set_shot_effector_strength(const vector2 value) const -> void
	{
		memory_handler::write<vector2>(
			shot_effector + offset::procedural_weapon_animation::shoteffector::recoil_strength_xy, value);

		memory_handler::write<vector2>(
			shot_effector + offset::procedural_weapon_animation::shoteffector::recoil_strength_z, value);
	}

	auto get_camera_position() const -> vector3
	{
		return memory_handler::read<vector3>(
			address + offset::procedural_weapon_animation::camera_position);
	}

	auto set_camera_position(const vector3 value) const -> void
	{
		memory_handler::write<vector3>(
			address + offset::procedural_weapon_animation::camera_position, value);
	}
};