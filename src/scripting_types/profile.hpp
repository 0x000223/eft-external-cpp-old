/*****************************************************************//**
 * \file   profile.hpp
 * \brief  
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "offset.hpp"
#include "memory.hpp"

/**
 * @brief Class which represents EFT.Profile
 */
class profile
{
private:

	/**
	 * @brief Address of this instance
	 */
	address_t m_address;

	/**
	 * @brief Address of Info class
	 */
	address_t m_info_address;

	//e_player_side side;

	//std::string side_name;

	/*auto parse_side_name() const -> std::string
	{
		switch(side)
		{
		case Bear:
			return std::string("Bear");

		case Usec:
			return std::string("Usec");

		case Savage:
			return std::string("Savage");

		default:
			return std::string("");
		}
	}*/

public:

	/**
	 * @brief
	 */
	std::wstring m_id;

	/**
	 * @brief Represents AccountId field in EFT.Profile class
	 */
	std::wstring m_account_id;

	/**
	 * @brief Represents GroupId in Info class
	 */
	std::wstring m_group_id;

	/**
	 * @brief Represents Nickname field in Info class
	 */
	std::wstring m_nickname;

	profile() 
		: m_address(0), m_info_address(0)
	{}

	explicit profile(const address_t address) 
		: m_address(address),
		m_info_address(memory::read<address_t>(address + O_PROFILE_INFO)),
		m_nickname(memory::read_wide_string(m_info_address + O_PROFILE_INFO_NICKNAME))
	{}
};

#endif