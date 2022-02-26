/**
 * @file math.hpp
 * @date 14/02/2022
 * 
 */

#ifndef MATH_HPP
#define MATH_HPP

#include <math.h>

/**
 * @brief
 */
struct vector2
{
	float x, y;

	static vector2 zero;

	bool operator !() const {
		return !this->x && !this->y;
	}

	vector2 operator +(vector2 other) const {
		return vector2 {
			.x = this->x + other.x, 
			.y = this->y + other.y
		};
	}

	vector2 operator*(float scalar) const {
		return vector2 {
			.x = this->x * scalar,
			.y = this->y * scalar
		};
	}

	bool operator ==(const vector2 other) const {
		if (this->x == other.x 
			&& this->y == other.y) {
			return true;
		}
		return false;
	}

	float distance(const vector2 other) const {
		auto const a = this->x - other.x;
		auto const b = this->y - other.y;

		return sqrtf(a * a + b * b);
	}
};

/**
 * @brief
 */
struct vector3
{
	float x, y, z;

	static vector3 zero;

	vector3 operator -(const vector3 other) const
	{
		vector3 ret {
			.x = this->x - other.x,
			.y = this->y - other.y,
			.z = this->z - other.z,
		};

		return ret;
	}

	vector3 operator *(const float other) const {
		return vector3(this->x * other, this->y * other);
	}

	bool operator ==(const vector3 other) const {
		if (this->x == other.x 
			&& this->y == other.y 
			&& this->z == other.z) {
			return true;
		}
		return false;
	}

	auto distance(const vector3 other) const -> float
	{
		auto const a = this->x - other.x;
		auto const b = this->y - other.y;
		auto const c = this->z - other.z;

		return sqrtf(a * a + b * b + c * c);
	}

	float length() const {
		auto const temp = powf(this->x, 2.f) + powf(this->y, 2.f) + powf(this->z, 2.f);
		return sqrtf(temp);
	}

	static float distance(vector3& first, vector3& second) {
		auto const a = first.x - second.x;
		auto const b = first.y - second.y;
		auto const c = first.z - second.z;

		return sqrtf(a * a + b * b + c * c);
	}

	static vector2 calculate_angle(const vector3 from, const vector3 to) {
		auto const diff = from - to;
		auto const length = diff.length();

		vector2 ret {
			.x = -atan2f(diff.x, -diff.z),
			.y =  asinf(diff.y / length)
		};

		return ret * 57.29578;
	}
};

/**
 * @brief
 */
struct vector4
{
	float x, y, z, w;
};

/**
 * @brief
 */
struct matrix34
{
	vector4 vec0;
	vector4 vec1;
	vector4 vec2;
};

/**
 * @brief
 */
struct matrix44
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;

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

#endif