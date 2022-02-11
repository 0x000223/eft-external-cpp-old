#pragma once
#include <string>

#include "offset.hpp"
#include "memory_handler.hpp"

class exfil_point
{
	// EFT.Interactive.ExfiltrationPoint
	
	uintptr_t address;

	std::wstring name;

public:

	explicit exfil_point(const uintptr_t addr) : address(addr)
	{
		auto settings =
			memory_handler::read<uintptr_t>(addr + offset::exfil_point::exfil_settings);

		name =
			memory_handler::read_wide_string(addr + offset::exfil_point::settings::name);
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_name() const -> std::wstring
	{
		return name;
	}
};