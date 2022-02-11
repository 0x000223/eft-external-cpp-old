#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"

struct color
{
private:
	
	float red;
	float green;
	float blue;
	float alpha;

	uintptr_t address;

public:

	color() = default;

	explicit color(const uintptr_t addr) : address(addr)
	{
		red = memory_handler::read<float>(address + offset::color::red);
		green = memory_handler::read<float>(address + offset::color::green);
		blue = memory_handler::read<float>(address + offset::color::blue);
		alpha = memory_handler::read<float>(address + offset::color::alpha);
	}

	auto get_address() const -> uintptr_t
	{
		return address;
	}
	
	auto get_red() const -> float
	{
		return alpha;
	}

	auto set_red(const float value)
	{
		memory_handler::write<float>(address + offset::color::red, value);

		red = value;
	}

	auto get_green() const -> float
	{
		return green;
	}

	auto set_green(const float value)
	{
		memory_handler::write<float>(address + offset::color::green, value);

		green = value;
	}

	auto get_blue() const -> float
	{
		return blue;
	}

	auto set_blue(const float value)
	{
		memory_handler::write<float>(address + offset::color::blue, value);

		blue = value;
	}

	auto get_alpha() const -> float
	{
		return alpha;
	}

	auto set_alpha(const float value)
	{
		memory_handler::write<float>(address + offset::color::alpha, value);

		alpha = value;
	}
};