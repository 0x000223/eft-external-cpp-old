/**
 * @file profile.hpp
 * @date 12/02/2022
 */

#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <string>

#include "offset.hpp"
#include "memory.hpp"
#include "e_player_side.h"

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

	std::wstring id;

	std::wstring account_id;

	std::wstring nickname;

	std::wstring group_id;

	e_player_side side;

	std::string side_name;

	auto parse_side_name() const -> std::string
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
	}

public:

	profile() 
		: m_address(0)
	{}

	explicit profile(const address_t address) 
		: m_address(address)
	{
		id = 
			memory_handler::read_wide_string(addr + offset::player::profile::id);

		account_id = 
			memory_handler::read_wide_string(addr + offset::player::profile::account_id);

		auto info =
			memory_handler::read<uintptr_t>(addr + offset::player::profile::profile_info);

		nickname =
			memory_handler::read_wide_string(info + offset::profile::info::nickname);

		group_id =
			memory_handler::read_wide_string(info + offset::profile::info::group_id);

		side = 
			static_cast<e_player_side>(
				memory_handler::read<int>(info + offset::profile::info::side));

		side_name = parse_side_name();
	}

	auto get_id() const -> std::wstring
	{
		return id;
	}

	auto get_account_id() const -> std::wstring
	{
		return account_id;
	}

	auto get_nickname() const -> std::wstring
	{
		return nickname;
	}

	auto get_group_id() const -> std::wstring
	{
		return group_id;
	}

	auto get_side() const -> e_player_side
	{
		return side;
	}

	auto get_side_name() const -> std::string
	{
		return side_name;
	}
};

#endif