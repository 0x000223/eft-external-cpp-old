#pragma once
#include <cstdint>
#include <emmintrin.h>
#include <xmmintrin.h>

#include "memory_handler.hpp"
#include "offset.hpp"
#include "utility.hpp"

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#pragma warning (disable : 26451)

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

	static auto get_position(uintptr_t transform) -> vector3
	{
		constexpr __m128 mul_vec0 = { -2.f,  2.f, -2.f, 0.f };
		constexpr __m128 mul_vec1 = {  2.f, -2.f, -2.f, 0.f };
		constexpr __m128 mul_vec2 = { -2.f, -2.f,  2.f, 0.f };

		auto transform_internal = memory_handler::read<uintptr_t>(transform + 0x10);

		auto matrix = memory_handler::read<uintptr_t>(transform_internal + 0x38);
		auto index  = memory_handler::read<int>(transform_internal + 0x40);

		auto matrix_list = memory_handler::read<uintptr_t>(matrix + 0x18);
		auto index_list  = memory_handler::read<uintptr_t>(matrix + 0x20);

		auto matrix_size = sizeof(matrix34) * index + sizeof(matrix34);
		auto index_size  = sizeof(int)      * index + sizeof(int);

		auto* matrix_buffer = memory_handler::read_bytes(matrix_list, matrix_size);
		auto* index_buffer	= memory_handler::read_bytes(index_list, index_size);
		
		if(!matrix_buffer || !index_buffer)
		{
			free(matrix_buffer);
			free(index_buffer);

			return vector3 { 0 };
		}

		auto result = *(__m128*)((uint64_t)matrix_buffer + 0x30 * (uint64_t)index);

		auto transform_index = *(int*)((uint64_t) index_buffer + 0x4 * (uint64_t)index);

		while(transform_index >= 0)
		{
			auto matrix_34 = *(matrix34*)((uint64_t)matrix_buffer + 0x30 * (uint64_t)transform_index);

				__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix_34.vec1), 0x00));	// xxxx
				__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix_34.vec1), 0x55));	// yyyy
				__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix_34.vec1), 0x8E));	// zwxy
				__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix_34.vec1), 0xDB));	// wzyw
				__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix_34.vec1), 0xAA));	// zzzz
				__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix_34.vec1), 0x71));	// yxwy
				__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix_34.vec2), result);
 
				result = _mm_add_ps(
					_mm_add_ps(
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(xxxx, mul_vec1), zwxy),
									_mm_mul_ps(_mm_mul_ps(yyyy, mul_vec2), wzyw)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(zzzz, mul_vec2), wzyw),
									_mm_mul_ps(_mm_mul_ps(xxxx, mul_vec0), yxwy)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(yyyy, mul_vec0), yxwy),
									_mm_mul_ps(_mm_mul_ps(zzzz, mul_vec1), zwxy)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
							tmp7)), *(__m128*)(&matrix_34.vec0));
 
				transform_index = *(int*)((uint64_t)index_buffer + 0x4 * (uint64_t)transform_index);
		}

		free(matrix_buffer);
		free(index_buffer);

		return vector3( result.m128_f32[0], result.m128_f32[1], result.m128_f32[2] );
	}
};

#endif