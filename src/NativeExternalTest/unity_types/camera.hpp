#pragma once
#include <cstdint>

#include "memory_handler.hpp"
#include "offset.hpp"
#include "managers.hpp"
#include "game_object.hpp"
#include "unity.hpp"
#include "component.hpp"
#include "utility.hpp"
#include "raid_instance.hpp"

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

	auto get_view_matrix() const -> matrix44
	{
		return memory_handler::read<matrix44>(address + offset::camera::view_matrix);
	}

	static auto world_to_screen(const vector3& pos) -> vector2
	{
		if(!raid_instance::main_camera_component)
		{
			return vector2(0,0);
		}
			
		auto temp = raid_instance::main_camera_component->get_view_matrix();
		
		auto const view_matrix = matrix44::transpose(temp);

		const vector3 up	= { view_matrix._21, view_matrix._22, view_matrix._23 };
		const vector3 right	= { view_matrix._11, view_matrix._12, view_matrix._13 };

		vector2 ret { 0,0 };
		
		const float w =
			{
				view_matrix._41 * pos.x +
				view_matrix._42 * pos.y +
				view_matrix._43 * pos.z +
				view_matrix._44
			};

		if(w < 0.1f)
		{
			return vector2 { 0 };
		}
		
		ret.x =
			{
				view_matrix._11 * pos.x +
				view_matrix._12 * pos.y +
				view_matrix._13 * pos.z +
				view_matrix._14
			};

		ret.y =
			{
				view_matrix._21 * pos.x +
				view_matrix._22 * pos.y +
				view_matrix._23 * pos.z +
				view_matrix._24
			};

		ret.x = ( 1920.f / 2.f ) * ( 1.f + ret.x / w ); // TODO - refactor hardcoded monitor dimensions
		ret.y = ( 1080.f / 2.f ) * ( 1.f - ret.y / w );

		return ret;
	}
	
	static auto get_main_camera() -> camera*
	{
		uint16_t main_camera_tag = 5;
		
		auto camera_game_object = game_object::find_with_tag(main_camera_tag);

		if(!camera_game_object)
		{
			return nullptr;
		}
		
		auto camera_type = unity::find_type_by_name("Camera");
		
		auto camera_component = game_object::query_component_by_type(camera_game_object, camera_type);

		return new camera( camera_component.get_address() );
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