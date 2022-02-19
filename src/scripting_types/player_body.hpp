#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "skeleton.hpp"
#include "transform.hpp"

/**
 * @brief Class which represents EFT.PlayerBody
 */
class player_body : public component
{
private:

public:

	player_body()
		: component()
	{}

	explicit player_body(const address_t address)
		: component(address)
	{}
};

class player_body
{
	// EFT.PlayerBody
	
	uintptr_t address;

	std::shared_ptr<skeleton> skeleton_root_joint;

	struct bone_transforms
	{
		transform root;
		transform pelvis;
		transform left_tigh_1;
		transform left_tigh_2;
		transform left_calf;
		transform left_foot;
		transform right_tigh_1;
		transform right_tigh_2;
		transform right_calf;
		transform right_foot;
		transform spine_1;
		transform spine_2;
		transform spine_3;
		transform left_upper_arm;
		transform left_forearm_1;
		transform left_forearm_2;
		transform left_forearm_3;
		transform right_upperarm;
		transform right_forearm_1;
		transform right_forearm_2;
		transform right_forearm_3;
		transform neck;
		transform head;
	};

	auto set_bone_transforms() const -> void
	{
		auto skeleton_transforms = skeleton_root_joint->get_values();

		bones->root				= skeleton_transforms[13];
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

public:

	std::shared_ptr<bone_transforms> bones;

	std::vector<std::pair<transform, transform>> bone_links;
	
	explicit player_body(const uintptr_t addr) : address(addr)
	{
		skeleton_root_joint = 
			std::make_shared<skeleton>(
				memory_handler::read<uintptr_t>(
					address + offset::player::playerbody::sekeleton_root_joint));

		if(skeleton_root_joint->get_keys().empty())
		{
			return;
		}

		bones = std::make_shared<bone_transforms>();

		set_bone_transforms();
		
		bone_links = 
			{
				{ bones->head,				bones->neck				},
				{ bones->neck,				bones->spine_1			},
				{ bones->spine_1,			bones->pelvis			},
				{ bones->right_upperarm,	bones->neck				},
				{ bones->right_forearm_1,	bones->right_upperarm	},
				{ bones->right_forearm_2,	bones->right_forearm_1	},
				{ bones->right_forearm_3,	bones->right_forearm_2	},
				{ bones->left_upper_arm,	bones->neck				},
				{ bones->left_forearm_1,	bones->left_upper_arm	},
				{ bones->left_forearm_2,	bones->left_forearm_1	},
				{ bones->left_forearm_3,	bones->left_forearm_2	},
				{ bones->right_tigh_1,		bones->pelvis			},
				{ bones->right_tigh_2,		bones->right_tigh_1		},
				{ bones->right_calf,		bones->right_tigh_2		},
				{ bones->right_foot,		bones->right_calf		},
				{ bones->pelvis,			bones->left_tigh_1		},
				{ bones->left_tigh_1,		bones->left_tigh_2		},
				{ bones->left_tigh_2,		bones->left_calf		},
				{ bones->left_calf,			bones->left_foot		}
			};
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}
};