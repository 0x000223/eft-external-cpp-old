/*****************************************************************//**
 * \file   player_body.hpp
 * \brief  
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

#include <vector>
#include <array>

#include "memory.hpp"
#include "transform.hpp"

enum BoneEnum {
	Root = 0,
	Plevis = 1,
	LeftTigh1 = 2,
	LeftFoot = 5,
	RightFoot = 9,
	Spine1 = 10,
	RightUpperArm = 17,
	RightForearm1 = 18,
	Neck = 21,
	Head = 22,
};

/**
 * @brief Class which represents EFT.PlayerBody
 */
class playerbody : public component
{
private:

	/**
	 * @brief Address of Diz.Skinning.Skeleton instance
	 */
	address_t m_skeleton_root_join_address;

	/**
	 * @brief Indices of needed bones for drawing an optimal player skeleton
	 */
	std::array<int, 23> bone_indices = {
		13, 14, 15, 16, 17, 18, 20, 21, 22, 23, 29, 36, 37, 90, 91,
		92, 93, 111, 112, 113, 114, 132, 133
	};

	

	std::vector<transform> parse_transforms();

public:

	/**
	 * @brief Player bones transforms of type UnityEngine::Transform
	 */
	std::vector<transform> m_transforms;

	/**
	 * @brief Player bone positions of type Vector3
	 */
	std::vector<vector3> m_positions;

	/**
	 * @brief Indices of bone links for single skeleton draw iteration
	 */
	std::array<int, 34> bone_link_indices = {
		22, 21, 21, 2, 17, 21, 18, 17, 19, 18,
		20, 19, 13, 21, 14, 13, 15, 14, 16, 15,
		6, 2, 7, 6, 8, 7, 9, 8, 2, 3, 3, 4, 4, 5
	};

	playerbody()
		: component(), m_skeleton_root_join_address(0)
	{}

	explicit playerbody(const address_t address)
		: component(address),
		m_skeleton_root_join_address(memory::read<address_t>(address + O_PLAYERBODY_SKELETONROOTJOINT)),
		m_transforms(parse_transforms()),
		m_positions(23)
	{}
};