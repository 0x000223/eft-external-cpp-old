#pragma once
#include <cstdint>
#include <string>

#include "memory_handler.hpp"
#include "offset.hpp"

#ifndef STRING_T_HPP
#define STRING_T_HPP

class system_string
{
	// System.String
	
public:

	uintptr_t address;

	uint32_t length;

	std::wstring data;
	
	explicit system_string(const uintptr_t addr) : address(addr)
	{
		length = 
			memory_handler::read<uint32_t>(addr + offset::string::length);

		auto* buffer = 
			static_cast<wchar_t*>(
				memory_handler::read_bytes(
					addr + offset::string::start, static_cast<size_t>(length) * 2)); // Unicode characters

		data = std::wstring(buffer);
	}
};

#endif