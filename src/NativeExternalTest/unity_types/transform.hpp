#pragma once
#include <cstdint>

#include "memory_handler.hpp"
#include "offset.hpp"

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

class transform	// Inherits from Component
{

	// TODO
	// FindTransformWithName(), Find(), 
	
public:

	uintptr_t address;

	unsigned child_count;
	
	explicit transform(const uintptr_t addr) : address(addr)
	{
		child_count = 
			memory_handler::read<unsigned>(addr + offset::transform::child_count);
	}

	static auto get_parent(const uintptr_t transform_address) -> uintptr_t
	{
		return memory_handler::read<uintptr_t>(
			transform_address + offset::transform::parent);
	}

	static auto get_root(const uintptr_t transform_address) -> uintptr_t
	{
		auto transform = transform_address;

		while(transform)
		{
			transform = 
				memory_handler::read<uintptr_t>(transform + offset::transform::parent);
		}

		return transform;
	}
};

#endif