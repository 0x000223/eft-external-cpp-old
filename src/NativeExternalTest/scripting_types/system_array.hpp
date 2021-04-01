#pragma once
#include <cstdint>
#include <vector>

#include "memory_handler.hpp"
#include "offset.hpp"

#ifndef ARRAY_T_HPP
#define ARRAY_T_HPP

template<typename T>
class system_array
{
	// System.Array
	
public:

	uintptr_t address;

	uint32_t count;
	
	std::vector<T> data;

	explicit system_array(const uintptr_t addr) : address(addr)
	{
		count = 
			memory_handler::read<uint32_t>(addr + offset::array::count);

		for(auto i = 0; i < count; i++)
		{
			auto address = 
				memory_handler::read<T>(addr + offset::array::base + i * 8);

			data.push_back(T(address)); // Try to invoke constructor on generic type
		}
	}
};

#endif ARRAY_T_HPP