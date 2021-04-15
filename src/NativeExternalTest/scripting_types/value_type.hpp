#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

struct value_type
{
	// E6D8
	
private:

	uintptr_t address;

public:

	explicit value_type(const uintptr_t addr) : address(addr) { }

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_current() const -> float
	{
		return memory_handler::read<float>(
			address + offset::value_type::current);
	}

	auto get_maximum() const -> float
	{
		return memory_handler::read<float>(
			address + offset::value_type::maximum);
	}

	auto get_minimum() const -> float
	{
		return memory_handler::read<float>(
			address + offset::value_type::minimum);
	}

	auto get_normalized() const -> float
	{
		return get_current() / get_maximum();
	}
};