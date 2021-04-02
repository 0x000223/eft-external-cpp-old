#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "skeleton.hpp"

class player_body
{
	// EFT.PlayerBody
	
	uintptr_t address;

	std::shared_ptr<skeleton> skeleton_root_joint;

	struct bone_transforms
	{
		uintptr_t pelvis;
		uintptr_t left_tigh_1;
		uintptr_t left_tigh_2;
		uintptr_t left_calf;
		uintptr_t left_foot;
		uintptr_t right_tigh_1;
		uintptr_t right_tigh_2;
		uintptr_t right_calf;
		uintptr_t right_foot;
		uintptr_t spine_1;
		uintptr_t spine_2;
		uintptr_t spine_3;
		uintptr_t left_upper_arm;
		uintptr_t left_forearm_1;
		uintptr_t left_forearm_2;
		uintptr_t left_forearm_3;
		uintptr_t right_upperarm;
		uintptr_t right_forearm_1;
		uintptr_t right_forearm_2;
		uintptr_t right_forearm_3;
		uintptr_t neck;
		uintptr_t head;
	};
	
public:

	std::shared_ptr<bone_transforms> bones;
	
	explicit player_body(const uintptr_t addr) : address(addr)
	{
		auto skeleton_address = 
			memory_handler::read<uintptr_t>(addr + offset::player::playerbody::sekeleton_root_joint);

		skeleton_root_joint = std::make_shared<skeleton>(skeleton_address);

		bones = std::make_shared<bone_transforms>();

		set_bone_transforms();
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_skeleton() const -> std::shared_ptr<skeleton>
	{
		return skeleton_root_joint;
	}

	auto set_bone_transforms() const -> void
	{
		auto skeleton_transforms = skeleton_root_joint->get_values();
		
		bones->pelvis			= skeleton_transforms[14];
		bones->left_tigh_1		= skeleton_transforms[15];
		bones->left_tigh_2		= skeleton_transforms[16];
		bones->left_calf		= skeleton_transforms[17];
		bones->left_foot		= skeleton_transforms[18];
		bones->right_tigh_1		= skeleton_transforms[20];
		bones->right_tigh_2		= skeleton_transforms[21];
		bones->right_calf		= skeleton_transforms[22];
		bones->right_foot		= skeleton_transforms[23];
		bones->spine_1			= skeleton_transforms[29];
		bones->spine_2			= skeleton_transforms[36];
		bones->spine_3			= skeleton_transforms[37];
		bones->left_upper_arm	= skeleton_transforms[90];
		bones->left_forearm_1	= skeleton_transforms[91];
		bones->left_forearm_2	= skeleton_transforms[92];
		bones->left_forearm_3	= skeleton_transforms[93];
		bones->right_upperarm	= skeleton_transforms[111];
		bones->right_forearm_1	= skeleton_transforms[112];
		bones->right_forearm_2	= skeleton_transforms[113];
		bones->right_forearm_3	= skeleton_transforms[114];
		bones->neck				= skeleton_transforms[132];
		bones->head				= skeleton_transforms[133];
	}
};