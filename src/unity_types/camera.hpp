/**
 * @file camera.hpp
 * @date 12/02/2022
 * 
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "game_object.hpp"
#include "component.hpp"
#include "../math.hpp"

/**
 * @brief Represents UnityEngine::Camera class
 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/Camera.html
 */
class camera : public component
{
private:
	
public:

	camera() 
		: component()
	{}

	explicit camera(const address_t address) 
		: component(address)
	{}

	/**
	 * @brief Returns matrix that transforms from world to camera space - referred to as 'view matrix'
	 */
	matrix44 get_world_to_camera_matrix() const;

	/**
	 * @brief Transforms position from world space to screen space
	 */
	vector2& world_to_screen(const vector3& pos);

	/**
	 * @brief
	 */
	float get_fov() const;
};

#endif
