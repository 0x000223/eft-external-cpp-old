
#pragma once
#include <string>

#include "offset.hpp"
#include "memory_handler.hpp"

class player_profile
{
	uintptr_t address;

	std::wstring id;

	std::wstring account_id;

	std::wstring nickname;

	std::wstring group_id;

	int32_t side;
	
public:

	explicit player_profile(const uintptr_t addr) : address(addr)
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
			memory_handler::read<int32_t>(info + offset::profile::info::side);
	}

	auto get_address() const -> uintptr_t
	{
		return address;
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
};