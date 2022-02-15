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

/**
 * @brief Class which represents UnityEngine::Transform
 */
class transform : public component
{
	
public:

	transform() 
		: component()
	{}
	
	explicit transform(const address_t address)
		: component(address) 
	{}
	
	/**
	 * @brief Retruns the world space position of the Transform
	 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/Transform-position.html
	 */
	vector3 get_position() const;
};

#endif