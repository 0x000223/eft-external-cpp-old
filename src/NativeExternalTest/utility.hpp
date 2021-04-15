#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include <cmath>

#pragma warning (disable : 4996)

struct vector2
{
	float x,y;

	auto operator ! () const -> bool
	{
		return !this->x && !this->y;
	}

	auto distance(const vector2 other) const -> float
	{
		auto const a = this->x - other.x;
		auto const b = this->y - other.y;

		return sqrtf(a * a + b * b);
	}
};

struct vector3
{
	float x,y,z;

	auto operator -(const vector3 other) const -> vector3
	{
		vector3 ret
		{
			ret.x = this->x - other.x,
			ret.y = this->y - other.y,
			ret.z = this->z - other.z,
		};

		return ret;
	}

	auto operator *(const float other) const -> vector3
	{
		return vector3(this->x * other, this->y * other);
	}
	
	auto distance(const vector3 other) const -> float
	{
		auto const a = this->x - other.x;
		auto const b = this->y - other.y;
		auto const c = this->z - other.z;

		return sqrtf(a * a + b * b + c * c);
	}

	auto length() const -> float
	{
		auto const temp = powf(this->x, 2.f) + powf(this->y, 2.f) + powf(this->z, 2.f);

		return sqrtf(temp);
	}
	
	static auto distance(vector3& first, vector3& second) -> float
	{
		auto const a = first.x - second.x;
		auto const b = first.y - second.y;
		auto const c = first.z - second.z;

		return sqrtf(a * a + b * b + c * c);
	}

	static auto calculate_angle(const vector3 from, const vector3 to) -> vector2
	{
		auto const diff = from - to;
		auto const length = diff.length();

		vector2 ret
		{
			ret.x = asinf(diff.y / length),
			ret.y = - atan2(diff.x, -diff.z),
		};

		return vector2(ret.x * 57.29578, ret.y * 57.29578);
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