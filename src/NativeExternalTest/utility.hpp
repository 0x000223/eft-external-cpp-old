#pragma once
#include <string>

#ifndef UTILITY_HPP
#define UTILITY_HPP

// TODO refactor this mess

namespace imported
{
	extern "C" __declspec(dllimport) auto get_process_id(const wchar_t* process_name) -> DWORD;

	extern "C" __declspec(dllimport) auto create_overlay(const wchar_t* text) -> HWND;
}

namespace utility
{
	inline auto get_process_id(std::wstring process_name) -> DWORD
	{
		return imported::get_process_id(process_name.data());
	}
}

#endif