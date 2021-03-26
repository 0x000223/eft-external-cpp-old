#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "memory_handler.hpp"
#include "offset.hpp"
#include "string_t.hpp"
#include "process_state.hpp"
#include "managers.hpp"
#include "component.hpp"
#include "unity.hpp"

class game_object
{
	// GameObject
	// https://docs.unity3d.com/2018.4/Documentation/ScriptReference/GameObject.html

	// TODO
	// GetComponent(), GetComponents(), GetComponentInChildren(), GetComponentInParent(), Find(), FindObjectOfType(), FindObjectsOfType()
	
public:

	uintptr_t address;

	bool is_active_self;
	
	bool is_active;

	int layer;
	
	uint16_t tag;

	std::string name;

	uintptr_t transform;

	std::vector<component> component_array; // TODO - Method to populate component array
	
	uintptr_t component_count;
	
	explicit game_object(const uintptr_t addr) : address(addr)
	{
		auto name_address = 
			memory_handler::read<uintptr_t>(addr + offset::game_object::object_name);

		name = 
			memory_handler::read_narrow_string(name_address);

		tag =
			memory_handler::read<uint16_t>(addr + offset::game_object::tag);
		
		layer =
			memory_handler::read<int>(addr + offset::game_object::layer);

		is_active_self =
			memory_handler::read<bool>(addr + offset::game_object::active_self);
		
		is_active = 
			memory_handler::read<bool>(addr + offset::game_object::is_active);

		transform = 
			get_transform();

		component_count = 
			memory_handler::read<uintptr_t>(addr + offset::game_object::component_count);
	}

	auto get_transform() const -> uintptr_t // TODO - retrun transform component type instead of address
	{
		auto component_array = 
			memory_handler::read<uintptr_t>(address + offset::game_object::component_array);

		auto t2 = memory_handler::read<uintptr_t>(component_array + 0x8);					// First component (tends to be Transform)

		return memory_handler::read<uintptr_t>(t2 + 0x28);									// Transform chain 3
	}

	auto query_component_by_type(const uintptr_t unity_type) const -> uintptr_t
	{
		// Unity internal function

		auto temp_component_array = 
			memory_handler::read<uintptr_t>(address + offset::game_object::component_array);
		
		auto last_component =
			memory_handler::read<uintptr_t>(temp_component_array + 0x10 * component_count);

		if(temp_component_array == last_component)
		{
			return 0;
		}

		auto uint32_1 = memory_handler::read<uint32_t>(unity_type + 0x30);
		auto uint32_2 = memory_handler::read<uint32_t>(unity_type + 0x34);

		// Paste from IDA
		while(memory_handler::read<uint32_t>(temp_component_array) - uint32_1 >= uint32_2)
		{
			temp_component_array += 0x10;

			if(temp_component_array == last_component)
			{
				return 0;
			}
		}

		return memory_handler::read<uintptr_t>(temp_component_array + 0x8);
	}

	static auto get_active_objects() -> std::vector<game_object>
	{
		if(!managers::object_manager)
		{
			return std::vector<game_object>();
		}

		std::vector<game_object> active_objects;

		auto first_active_object = 
			memory_handler::read<uintptr_t>(
				managers::object_manager + offset::object_manager::active_objects);

		auto active_object = first_active_object;
		
		do
		{
			auto game_object_address = 
				memory_handler::read<uintptr_t>(active_object + 0x10); // Cached ptr

			active_objects.emplace_back( game_object(game_object_address) );

			active_object = 
				memory_handler::read<uintptr_t>(
					active_object + offset::object_manager::next_object);
			
		} while(active_object != first_active_object); // TODO => sometimes enters into a inifine loop

		return active_objects;
	}
	
	static auto get_tagged_objects() -> std::vector<game_object>
	{
		if(!managers::object_manager)
		{
			return std::vector<game_object>();
		}
		
		std::vector<game_object> tagged_objects;

		auto tagged_object = 
			memory_handler::read<uintptr_t>(
				managers::object_manager + offset::object_manager::tagged_objects);

		while(tagged_object != managers::object_manager)
		{
			auto game_object_address = 
				memory_handler::read<uintptr_t>(tagged_object + 0x10); // Cached ptr

			tagged_objects.emplace_back( game_object(game_object_address) );

			tagged_object = 
				memory_handler::read<uintptr_t>(tagged_object + offset::object_manager::next_object);
		}

		return tagged_objects;
	}

	static auto find(std::string game_object_name) // TODO - finish this meme
	{
		// https://docs.unity3d.com/ScriptReference/GameObject.Find.html
		
		if(!managers::object_manager)
		{
			return 0;
		}
		
	}
	
	static auto find_game_objects_with_tag(const uint16_t target_tag) -> std::vector<game_object>
	{
		// https://docs.unity3d.com/ScriptReference/GameObject.FindGameObjectsWithTag.html
		
		if(!managers::object_manager)
		{
			return std::vector<game_object>();
		}

		auto tagged_object = 
			memory_handler::read<uintptr_t>(managers::object_manager + offset::object_manager::tagged_objects);

		if(tagged_object == managers::object_manager)
		{
			return std::vector<game_object>();
		}

		std::vector<game_object> ret_game_objects;
		
		while(tagged_object != managers::object_manager)
		{
			auto ret = 
				game_object ( memory_handler::read<uintptr_t>(tagged_object + 0x10) ); // Catched ptr

			if(ret.tag == target_tag)
			{
				ret_game_objects.push_back(ret);
			}

			tagged_object = 
				memory_handler::read<uintptr_t>(tagged_object + offset::object_manager::next_object);
		}

		return ret_game_objects;
	}
	
	static auto find_with_tag(const uint16_t target_tag) -> game_object
	{
		// https://docs.unity3d.com/ScriptReference/GameObject.FindWithTag.html
		
		if(!managers::object_manager)
		{
			return game_object { 0 };
		}
		
		auto tagged_object = 
			memory_handler::read<uintptr_t>(
				managers::object_manager + offset::object_manager::tagged_objects);

		if(tagged_object == managers::object_manager)
		{
			return game_object { 0 };
		}

		while(tagged_object != managers::object_manager)
		{
			auto ret = 
				game_object(memory_handler::read<uintptr_t>(tagged_object + 0x10)); // cached_ptr

			if(ret.tag == target_tag)
			{
				return ret;
			}

			tagged_object = 
				memory_handler::read<uintptr_t>(tagged_object + offset::object_manager::next_object);
		}

		return game_object { 0 };
	}
};
