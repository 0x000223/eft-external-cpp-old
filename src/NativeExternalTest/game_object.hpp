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
	// GetComponent(),
	// GetComponents(),
	// GetComponentInChildren(),
	// GetComponentInParent(),
	// QueryComponentByExactType(Unity::Type const* )
	// GetComponentPtrAtIndex(int)
	// GetCullSceneMask(void)
	// GetComponentIndex(Unity::Component)
	
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
			memory_handler::read<uintptr_t>(addr + offset::game_object::name);

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

	

	auto get_components_by_name(std::string component_name) const
	{
		
	}

	auto reset() const -> void
	{
		// Unity internal

		memory_handler::write<uint32_t>(address + 0x50, 0); // TODO - clean offsets
		memory_handler::write<uint16_t>(address + 0x54, 0);
	}

	static auto query_component_by_type(game_object& game_object, const uintptr_t unity_type) -> uintptr_t
	{
		// Unity internal

		auto temp_component_array = 
			memory_handler::read<uintptr_t>(game_object.address + offset::game_object::component_array);
		
		auto last_component =
			memory_handler::read<uintptr_t>(temp_component_array + 0x10 * game_object.component_count);

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
		if(!managers::game_object_manager)
		{
			return std::vector<game_object>();
		}

		std::vector<game_object> active_objects;

		auto first_active_object = 
			memory_handler::read<uintptr_t>(
				managers::game_object_manager + offset::game_object_manager::active_objects);

		auto active_object = first_active_object;
		
		do
		{
			auto game_object_address = 
				memory_handler::read<uintptr_t>(active_object + 0x10); // Cached ptr

			active_objects.emplace_back( game_object(game_object_address) );

			active_object = 
				memory_handler::read<uintptr_t>(
					active_object + offset::game_object_manager::next_object);
			
		} while(active_object != first_active_object); // TODO - FIX while(active_object != last_active_object)

		return active_objects;
	}
	
	static auto get_tagged_objects() -> std::vector<game_object>
	{
		if(!managers::game_object_manager)
		{
			return std::vector<game_object>();
		}
		
		std::vector<game_object> tagged_objects;

		auto tagged_object = 
			memory_handler::read<uintptr_t>(
				managers::game_object_manager + offset::game_object_manager::tagged_objects);

		while(tagged_object != managers::game_object_manager)
		{
			auto game_object_address = 
				memory_handler::read<uintptr_t>(tagged_object + 0x10); // Cached ptr

			tagged_objects.emplace_back( game_object(game_object_address) );

			tagged_object = 
				memory_handler::read<uintptr_t>(tagged_object + offset::game_object_manager::next_object);
		}

		return tagged_objects;
	}
	
	static auto find(std::string game_object_name) -> game_object
	{
		// https://docs.unity3d.com/ScriptReference/GameObject.Find.html
		
		if(!managers::game_object_manager)
		{
			return game_object ( 0 );
		}

		auto tagged_object = 
			memory_handler::read<uintptr_t>(
				managers::game_object_manager + offset::game_object_manager::tagged_objects);

		auto active_object =
			memory_handler::read<uintptr_t>(
				managers::game_object_manager + offset::game_object_manager::active_objects);

		auto last_active_object =
			managers::game_object_manager + offset::game_object_manager::last_active_object;
		
		if(tagged_object == managers::game_object_manager) // Checking if there are any tagged objects
		{
			if(active_object == last_active_object) // Iterate active objects
			{
				// No game objects available

				return game_object ( 0 );
			}

			while(active_object != last_active_object)
			{
				auto object_address = 
					memory_handler::read<uintptr_t>(active_object + 0x10);

				auto ret_game_object = game_object( object_address );
				
				auto ret_transform = 
					find_active_transform_with_path(game_object_name, ret_game_object);

				if(ret_transform)
				{
					return ret_game_object;
				}
				
				active_object = 
					memory_handler::read<uintptr_t>(
						active_object + offset::game_object_manager::next_object);
			}
		}

		while(tagged_object != managers::game_object_manager) // Iterate tagged objects
		{
			auto object_address =
				memory_handler::read<uintptr_t>(tagged_object + 0x10);

			auto ret_game_object = game_object ( object_address );

			auto ret_transform =
				find_active_transform_with_path(game_object_name, ret_game_object);

			if(ret_transform)
			{
				return ret_game_object;
			}
			
			tagged_object = 
				memory_handler::read<uintptr_t>(
					tagged_object + offset::game_object_manager::next_object);
		}

		return game_object ( 0 );
	}

	static auto find_game_objects_with_tag(const uint16_t target_tag) -> std::vector<game_object>
	{
		// https://docs.unity3d.com/ScriptReference/GameObject.FindGameObjectsWithTag.html
		
		if(!managers::game_object_manager)
		{
			return std::vector<game_object>();
		}

		auto tagged_object = 
			memory_handler::read<uintptr_t>(managers::game_object_manager + offset::game_object_manager::tagged_objects);

		if(tagged_object == managers::game_object_manager)
		{
			return std::vector<game_object>();
		}

		std::vector<game_object> ret_game_objects;
		
		while(tagged_object != managers::game_object_manager)
		{
			auto ret = 
				game_object ( memory_handler::read<uintptr_t>(tagged_object + 0x10) ); // Catched ptr

			if(ret.tag == target_tag)
			{
				ret_game_objects.push_back(ret);
			}

			tagged_object = 
				memory_handler::read<uintptr_t>(tagged_object + offset::game_object_manager::next_object);
		}

		return ret_game_objects;
	}
	
	static auto find_with_tag(const uint16_t target_tag) -> game_object
	{
		// https://docs.unity3d.com/ScriptReference/GameObject.FindWithTag.html
		
		if(!managers::game_object_manager)
		{
			return game_object { 0 };
		}
		
		auto tagged_object = 
			memory_handler::read<uintptr_t>(
				managers::game_object_manager + offset::game_object_manager::tagged_objects);

		if(tagged_object == managers::game_object_manager)
		{
			return game_object { 0 };
		}

		while(tagged_object != managers::game_object_manager)
		{
			auto ret = 
				game_object(memory_handler::read<uintptr_t>(tagged_object + 0x10)); // cached_ptr

			if(ret.tag == target_tag)
			{
				return ret;
			}

			tagged_object = 
				memory_handler::read<uintptr_t>(tagged_object + offset::game_object_manager::next_object);
		}

		return game_object { 0 };
	}
	
	static auto find_active_transform_with_path(std::string game_object_name, game_object& target_game_object) -> uintptr_t
	{
		// Unity internal

		if(target_game_object.name != game_object_name)
		{
			return 0;
		}

		auto ret_transform = 
			query_component_by_type(target_game_object, unity::find_type_by_name("Transform") );

		if(!ret_transform)
		{
			return 0;
		}

		auto attached_game_object = game_object( 
			memory_handler::read<uintptr_t>(
				ret_transform + offset::component::attached_game_object) );

		if(attached_game_object.is_active)
		{
			return ret_transform;
		}

		return 0;
	}
};