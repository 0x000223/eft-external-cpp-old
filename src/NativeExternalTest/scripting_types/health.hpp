#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"

class health
{
	// E6DA

	uintptr_t address;

public:

	explicit health(const uintptr_t addr) : address(addr) { }

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
};