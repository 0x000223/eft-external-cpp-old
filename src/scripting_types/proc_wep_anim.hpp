
#ifndef PROC_WEP_ANIM_HPP
#define PROC_WEP_ANIM_HPP

#include "offset.hpp"
#include "memory.hpp"
#include "math.hpp"

class proc_wep_anim {

private:

	/**
	 * @brief Address of EFT.Animations.EProceduralAnimationMask
	 */
	address_t m_mask_address;

	/**
	 * @brief Address of ShotEffector class instance
	 */
	address_t m_shot_effector_address;

	/**
	 * @brief Address of EFT.Animations.BreathEffector class instance
	 */
	address_t m_breath_effector_address;

	/**
	 * @brief Address of WalkEffector class instance
	 */
	address_t m_walk_effector_address;

	/**
	 * @brief Address of MotionEffector class instance
	 */
	address_t m_motion_effector_address;

	/**
	 * @brief
	 */
	address_t m_force_effector_address;

public:

	/**
	 * @brief Address of current class instance
	 */
	address_t m_address;

	proc_wep_anim()
		: m_address(0), m_mask_address(0), m_shot_effector_address(0), m_breath_effector_address(0), m_walk_effector_address(0)
	{}

	explicit proc_wep_anim(const address_t address) 
		: m_address(address),
		m_mask_address(memory::read<address_t>(address + O_PROCWEPANIM_MASK)),
		m_shot_effector_address(memory::read<address_t>(address + O_PROCWEPANIM_SHOT)),
		m_breath_effector_address(memory::read<address_t>(address + O_PROCWEPANIM_BREATH)),
		m_walk_effector_address(memory::read<address_t>(address + O_PROCWEPANIM_WALK)),
		m_motion_effector_address(memory::read<address_t>(address + O_PROCWEPANIM_MOTION)),
		m_force_effector_address(memory::read<address_t>(address + O_PROCWEPANIM_FORCE))
	{}

	/**
	 * @brief
	 */
	void set_mask(const int value) const;

	/**
	 * @brief
	 */
	void set_shot_effector(const vector2 value, const float intensity) const;

	/**
	 * @brief
	 */
	void set_breath_effector(const float value) const;

	/**
	 * @brief
	 */
	void set_walk_effector(const float value) const;

	/**
	 * @brief
	 */
	void set_motion_effector(const float value) const;

	/**
	 * @brief
	 */
	void set_force_effector(const float value) const;
};

#endif