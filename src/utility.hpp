/*****************************************************************//**
 * \file   utility.hpp
 * \brief  
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <cmath>
#include <concepts>

#include "offset.hpp"
#include "memory.hpp"

namespace utility
{
	template<typename T>
	concept Integral = std::is_integral<T>::value;
	
	template<typename T>
	concept NonIntegral = !std::is_integral<T>::value;

	/**
	 * @brief Parses System.Collections.Generic.List<T>
	 */
	template<NonIntegral T>
	std::vector<T> parse_list(const address_t address) {

		const auto list_address = memory::read<address_t>(address);
		
		std::vector<T> ret;

		if (address == 0) {
			return ret;
		}

		const auto count = memory::read<int>(list_address + O_LIST_SIZE);
		const auto base = memory::read<address_t>(list_address + O_LIST_ITEMS);

		for (auto index = 0; index < count; ++index) {
			const auto addr = memory::read<address_t>(base + O_ARRAY_BASE + index * 0x8);
			ret.push_back(T(addr));
		}

		return ret;
	}

	template<Integral T>
	std::vector<T> parse_list(const address_t address) {

		const auto list_address = memory::read<address_t>(address);

		std::vector<T> ret;

		if (address == 0) {
			return ret;
		}

		const auto count = memory::read<int>(list_address + O_LIST_SIZE);
		const auto base = memory::read<address_t>(list_address + O_LIST_ITEMS);

		for (auto index = 0; index < count; ++index) {
			const auto value = memory::read<address_t>(base + O_ARRAY_BASE + index * 0x8);
			ret.push_back(value);
		}

		return ret;
	}

	std::string wide_to_narrow(const std::wstring& wide_string);
}

#endif