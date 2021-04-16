#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

class visor_effect
{
	// VisorEffect

private:

	uintptr_t address;

public:

	visor_effect() = default;

	explicit visor_effect(const uintptr_t addr) : address(addr) { }

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_intensity() const -> float
	{
		return memory_handler::read<float>(
			address + offset::visor_effect::intensity);
	}

	auto set_intensity(const float value) const -> void
	{
		return memory_handler::write<float>(
			address + offset::visor_effect::intensity, value);
	}

	auto get_velocity() const -> float
	{
		// No clue why its even inside this component

		return memory_handler::read<float>(
			address + offset::visor_effect::velocity);
	}
};