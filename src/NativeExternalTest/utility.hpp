#pragma once
#include <string>
#include <locale>
#include <codecvt>

#pragma warning (disable : 4996)

struct vector2
{
	float x,y;

	auto operator ! () const -> bool
	{
		return !this->x && !this->y;
	}
};

struct vector3
{
	float x,y,z;

	auto distance(vector3& other) const -> float
	{
		auto a = this->x - other.x;
		auto b = this->y - other.y;
		auto c = this->z - other.z;

		return sqrtf(a * a + b * b + c * c);
	}
	
	static auto distance(vector3& first, vector3& second) -> float
	{
		auto a = first.x - second.x;
		auto b = first.y - second.y;
		auto c = first.z - second.z;

		return sqrtf(a * a + b * b + c * c);
	}
};

struct vector4
{
	float x,y,z,w;
};

struct matrix34
{
	vector4 vec0;
	vector4 vec1;
	vector4 vec2;
};

struct matrix44
{
	float _11,_12,_13,_14;
	float _21,_22,_23,_24;
	float _31,_32,_33,_34;
	float _41,_42,_43,_44;

	auto static transpose(matrix44& other) -> matrix44
	{
		matrix44 ret
		{
			ret._11 = other._11,
			ret._12 = other._21,
			ret._13 = other._31,
			ret._14 = other._41,
			ret._21 = other._12,
			ret._22 = other._22,
			ret._23 = other._32,
			ret._24 = other._42,
			ret._31 = other._13,
			ret._32 = other._23,
			ret._33 = other._33,
			ret._34 = other._43,
			ret._41 = other._14,
			ret._42 = other._24,
			ret._43 = other._34,
			ret._44 = other._44,
		};

		return ret;
	}
};

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

	inline auto wide_to_narrow(const std::wstring& wide_string)
	{
		using convert_type = std::codecvt_utf8<wchar_t>;
		
		std::wstring_convert<convert_type, wchar_t> converter;

		return std::string { converter.to_bytes(wide_string) };
	}
}