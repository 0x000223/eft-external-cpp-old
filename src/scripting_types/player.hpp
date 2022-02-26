/*****************************************************************//**
 * \file   player.hpp
 * \brief  
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "offset.hpp"
#include "memory.hpp"
#include "math.hpp"
#include "utility.hpp"

#include "component.hpp"
#include "profile.hpp"
#include "playerbody.hpp"
#include "physical.hpp"
#include "proc_wep_anim.hpp"

/**
 * @brief Class which represents EFT.Player
 */
class player : public component
{
private:

	/**
	 * @brief Instance of Physical class
	 */
	physical m_physical;

public:

	/**
	 * @brief Instance of type EFT.Profile
	 */
	profile m_profile;

	/**
	 * @brief Instance of EFT.Playerbody
	 */
	playerbody m_playerbody;

	/**
	 * @brief Address of ProceduralWeaponAnimation instance
	 */
	proc_wep_anim m_proc_wep_anim;

	/**
	 * @brief Address of MovementContext instance
	 */
	address_t movement_context_address;

	/**
	 * @brief Address of EFT.Player.AbstractHandsController instance 
	 */
	address_t hands_controller_address;

	/**
	 * @brief Nickname field from Info class
	 */
	std::string m_name;

	/**
	 * @brief String representation of EPlayerSide enum
	 */
	std::string m_side;

	player()
		: component()
	{}
	
	explicit player(const address_t address)
		: component(address),
		m_profile(memory::read<address_t>(m_address + O_PLAYER_PROFILE)),
		m_name(utility::wide_to_narrow(m_profile.m_nickname)),
		m_playerbody(memory::read<address_t>(m_address + O_PLAYER_PLAYERBODY)),
		movement_context_address(memory::read<address_t>(m_address + O_PLAYER_MOVEMENTCONTEXT)),
		hands_controller_address(memory::read<address_t>(m_address + O_PLAYER_HANDSCONTROLLER)),
		m_physical(memory::read<address_t>(address + O_PLAYER_PHYSICAL)),
		m_proc_wep_anim(memory::read<address_t>(address + O_PLAYER_PROCEDURALWEPANIM))
	{}

	float get_health();

	float get_max_health();

	vector3 get_root_position();

	vector3 get_head_position();

	vector2 get_rotation() const;

	transform get_fireport();

	void set_rotation(const vector2 rotation) const;

	void fill_stamina(const float value) const;
};

#endif