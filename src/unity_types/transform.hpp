/**
 * @file transform.hpp
 * @date 15/02/2022
 * 
 */

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "offset.hpp"
#include "memory.hpp"
#include "math.hpp"
#include "component.hpp"

struct trsX { // sizeof=0x30
	// math::_float3 
	// math::_float4
	// math::_float3
};

/**
 * @brief Class which represents UnityEngine::Transform
 */
class transform : public component
{

private:

	/**
	 * @brief Index of current transform
	 */
	int index;

	/**
	 * @brief Address of TransformHierarchy structure
	 */
	address_t hierarchy_address;

	/**
	 * @brief
	 */
	address_t local_transforms_address;

	/**
	 * @brief
	 */
	address_t parent_indices_address;

	/**
	 * @brief
	 */
	std::vector<int> parent_indices;

public:

	transform() 
		: component()
	{}
	
	explicit transform(const address_t address)
		: component(address),
		hierarchy_address(memory::read<address_t>(address + O_TRANSFORM_ACCESS + O_TRANSFROM_ACCESS_HIERARCHY)),
		index(memory::read<int>(address + O_TRANSFORM_ACCESS + O_TRANSFORM_ACCESS_INDEX)),
		local_transforms_address(memory::read<address_t>(hierarchy_address + O_TRANSFORM_ACCESS_HIERARCHY_LOCALTRANSFORMS)),
		parent_indices_address(memory::read<address_t>(hierarchy_address + O_TRANSFORM_ACCESS_HIERARCHY_PARENTINDICES)),
		parent_indices(memory::read_many<int>(parent_indices_address, index + 1))
	{}
	
	/**
	 * @brief Retruns the world space position of the Transform
	 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/Transform-position.html
	 */
	vector3 get_position() const;
};

#endif