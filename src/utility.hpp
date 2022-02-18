
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <locale>
#include <codecvt>
#include <cmath>

#pragma warning (disable : 4996)

namespace utility
{
	inline auto wide_to_narrow(const std::wstring& wide_string)
	{
		if(wide_string.size() > 1000)
		{
			return std::string();
		}
		
		using convert_type = std::codecvt_utf8<wchar_t>;
		
		std::wstring_convert<convert_type, wchar_t> converter;

		return std::string { converter.to_bytes(wide_string) };
	}
}

#endif