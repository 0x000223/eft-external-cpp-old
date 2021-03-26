#pragma once
#include <cstdint>

#include "memory_handler.hpp"
#include "offset.hpp"
#include "managers.hpp"
#include "game_object.hpp"
#include "unity.hpp"
#include "component.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

class camera : public component
{
	// UnityEngine.Camera
	// https://docs.unity3d.com/ScriptReference/Camera.html

public:

	explicit camera(const uintptr_t addr) : component(addr)
	{
		// Handle constructor
	}

	auto get_fov() const -> float
	{
		return memory_handler::read<float>(address + offset::camera::fov);
	}

	auto set_fov(const float new_fov) const -> void
	{
		return memory_handler::write(address + offset::camera::fov, new_fov);
	}

	auto get_depth() const -> float
	{
		return memory_handler::read<float>(address + offset::camera::depth);
	}

	auto set_depth(const float new_depth) const -> void
	{
		return memory_handler::write(address + offset::camera::depth, new_depth);
	}
	
	static auto get_main_camera() -> camera
	{
		uint16_t main_camera_tag = 5;
		
		auto camera_game_object = game_object::find_with_tag(main_camera_tag);

		auto camera_type = unity::find_type_by_name("Camera");
		
		auto component_address = camera_game_object.query_component_by_type(camera_type);

		return camera ( component_address );
	}

	static auto get_all_cameras_count() -> unsigned
	{
		// Camera.allCamerasCount
		// https://docs.unity3d.com/2018.4/Documentation/ScriptReference/Camera-allCamerasCount.html
		
		if(!managers::render_manager)
		{
			return 0;
		}
		
		auto n1 = memory_handler::read<unsigned>(managers::render_manager + 0x18);

		auto n2 = memory_handler::read<unsigned>(managers::render_manager + 0x28);

		return n1 + n2;
	}
	
private:

	enum camera_type : int
	{
		Game,
		SceneView,
		Preview,
		VR,		
		Reflection,
	};
};

#endif