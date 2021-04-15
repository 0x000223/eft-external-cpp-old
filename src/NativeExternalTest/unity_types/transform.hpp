#pragma once
#include <cstdint>
#include <emmintrin.h>
#include <xmmintrin.h>

#include "memory_handler.hpp"
#include "offset.hpp"
#include "utility.hpp"
#include "component.hpp"

#pragma warning (disable : 26451)

class transform : public component
{
	// UnityEngine.Transform
	
public:

	transform() = default;
	
	explicit transform(const uintptr_t addr) : component(addr) { }
	
	auto get_parent() const -> uintptr_t
	{
		return memory_handler::read<uintptr_t>(
			address + offset::transform::parent);
	}

	auto get_root() const -> uintptr_t
	{
		auto parent = address;

		while(parent)
		{
			parent = 
				memory_handler::read<uintptr_t>(
					parent + offset::transform::parent);
		}

		return parent;
	}

	auto get_position() const -> vector3
	{
		constexpr __m128 mul_vec0 = { -2.f,  2.f, -2.f, 0.f };
		constexpr __m128 mul_vec1 = {  2.f, -2.f, -2.f, 0.f };
		constexpr __m128 mul_vec2 = { -2.f, -2.f,  2.f, 0.f };

		void* matrix_buffer = nullptr;
		void* index_buffer  = nullptr;

		int index = 0;
		
		try
		{
			auto transform_internal = memory_handler::read<uintptr_t>(address + 0x10);

			auto matrix = memory_handler::read<uintptr_t>(transform_internal + 0x38);
			index = memory_handler::read<int>(transform_internal + 0x40);

			auto matrix_list = memory_handler::read<uintptr_t>(matrix + 0x18);
			auto index_list  = memory_handler::read<uintptr_t>(matrix + 0x20);

			auto matrix_size = sizeof(matrix34) * index + sizeof(matrix34);
			auto index_size  = sizeof(int)      * index + sizeof(int);

			if(matrix_size > 25000)
			{
				return vector3(0,0,0); // TODO - bandaid temp fix
			}
			
			matrix_buffer = memory_handler::read_bytes(matrix_list, matrix_size);
			index_buffer  = memory_handler::read_bytes(index_list, index_size);
		}
		catch(...) { return vector3(0,0,0); }
		
		if(!matrix_buffer || !index_buffer)
		{
			free(matrix_buffer);
			free(index_buffer);

			return vector3(0,0,0);
		}

		auto result = 
			*reinterpret_cast<__m128*>( reinterpret_cast<uintptr_t>(matrix_buffer) + 0x30 * index );

		auto transform_index = 
			*reinterpret_cast<int*>( reinterpret_cast<uintptr_t>(index_buffer) + 0x4 * index );
		
		while(transform_index >= 0)
		{
			matrix34 matrix_34;

			try
			{
				matrix_34 = 
					*reinterpret_cast<matrix34*>( reinterpret_cast<uintptr_t>(matrix_buffer) + 0x30 * transform_index );
				
				__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>( &matrix_34.vec1 ), 0x00));
				__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>( &matrix_34.vec1 ), 0x55));
				__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>( &matrix_34.vec1 ), 0x8E));
				__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>( &matrix_34.vec1 ), 0xDB));
				__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>( &matrix_34.vec1 ), 0xAA));
				__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*reinterpret_cast<__m128i*>( &matrix_34.vec1 ), 0x71));
				
				__m128 tmp7 = _mm_mul_ps(*reinterpret_cast<__m128*>( &matrix_34.vec2 ), result);

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
							tmp7)), *reinterpret_cast<__m128*>( &matrix_34.vec0 ));

				transform_index = 
					*reinterpret_cast<int*>( reinterpret_cast<uintptr_t>(index_buffer) + 0x4 * transform_index );
				
			} catch (...) { free(matrix_buffer); free(index_buffer); return vector3(0,0,0); }
		}

		free(matrix_buffer);
		free(index_buffer);

		return vector3( result.m128_f32[0], result.m128_f32[1], result.m128_f32[2] );
	}
};