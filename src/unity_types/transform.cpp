#include "transform.hpp"

#include <emmintrin.h>
#include <xmmintrin.h>

vector3 transform::get_position() const {

	static __m128 xmm0 = { -2.f, -2.f,  2.f, 0.f };
	static __m128 xmm1 = { -2.f,  2.f, -2.f, 0.f };
	static __m128 xmm2 = {  2.f, -2.f, -2.f, 0.f };

	auto local_transforms = memory::read_many<__m128>(local_transforms_address, 3 * index + 3);
	if (local_transforms.empty() || parent_indices.empty()) {
		return vector3 { 0 };
	}

	auto v6 = parent_indices[index];

	__m128 result = local_transforms[3 * index];

	while (v6 >= 0)
	{
		__m128i q = _mm_castps_si128(local_transforms[3 * v6 + 1]);

		auto v10 = _mm_castps_si128(_mm_mul_ps(local_transforms[3 * v6 + 2], result));
		auto v11 = _mm_castsi128_ps(_mm_shuffle_epi32(q, 0x55));
		auto v12 = _mm_castsi128_ps(_mm_shuffle_epi32(q, 0x0));
		auto v13 = _mm_castsi128_ps(_mm_shuffle_epi32(q, 0xAA));
		auto v14 = _mm_castsi128_ps(_mm_shuffle_epi32(q, 0x8E));
		auto v15 = _mm_castsi128_ps(_mm_shuffle_epi32(q, 0xDB));
		auto v16 = _mm_castsi128_ps(_mm_shuffle_epi32(q, 0x71));

		__m128 v17 = _mm_add_ps(
						_mm_add_ps(
							_mm_add_ps(
								_mm_mul_ps(
									_mm_sub_ps(
										_mm_mul_ps(_mm_mul_ps(v13, xmm0), v15),
										_mm_mul_ps(_mm_mul_ps(v12, xmm1), v16)),
											_mm_castsi128_ps(_mm_shuffle_epi32(v10, 0x55))),
										_mm_mul_ps(
											_mm_sub_ps(
												_mm_mul_ps(_mm_mul_ps(v12, xmm2), v14),
												_mm_mul_ps(_mm_mul_ps(v11, xmm0), v15)),
											_mm_castsi128_ps(_mm_shuffle_epi32(v10, 0xAA)))),
										_mm_add_ps(
											_mm_mul_ps(
												_mm_sub_ps(
													_mm_mul_ps(_mm_mul_ps(v11, xmm1), v16),
													_mm_mul_ps(_mm_mul_ps(v13, xmm2), v14)),
												_mm_castsi128_ps(_mm_shuffle_epi32(v10, 0))),
											_mm_castsi128_ps(v10))),
										local_transforms[3 * v6]);

		v6 = parent_indices[v6];
		result = v17;
	}

	return vector3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
}
