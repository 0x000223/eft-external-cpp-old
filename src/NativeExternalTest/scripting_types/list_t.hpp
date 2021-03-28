#pragma once
#include <cstdint>
#include <vector>

#include "memory_handler.hpp"
#include "offset.hpp"

#ifndef LIST_T_HPP
#define LIST_T_HPP

template<typename T>
class list_t
{
public:

	uintptr_t address;

	uint32_t count;

	std::vector<T> data;
	
	explicit list_t(const uintptr_t addr) : address(addr)
	{
		count = 
			memory_handler::read<uint32_t>(addr + offset::generic_list::count);

		auto base = 
			memory_handler::read<uintptr_t>(addr + offset::generic_list::base) + offset::array::base;
		
		for(unsigned index = 0; index < count; index++)
		{
			auto address = memory_handler::read<uintptr_t>(base + index * 8);

			data.push_back(T(address));	// Try to invoke constructor on generic type
		}
	}
};

#endif