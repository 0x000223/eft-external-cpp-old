#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "game_object.hpp"

class component
{
	// Component
	// https://docs.unity3d.com/ScriptReference/Component.html

public:

	uintptr_t address;

	std::string name;

	uint16_t tag;			// Tag is game object its attached to

	uintptr_t transform;		// Transform of the game object its attached to

	explicit component(const uintptr_t addr) : address(addr)
	{
		name = get_name();
	}

	auto get_name() const -> std::string
	{
		auto component_class = memory_handler::read<uintptr_t>(address + 0x28);

		auto temp1 = memory_handler::read<uintptr_t>(component_class);

		auto temp2 = memory_handler::read<uintptr_t>(temp1);

		auto name_address = memory_handler::read<uintptr_t>(temp2 + 0x48);

		return memory_handler::read_narrow_string(name_address);
	}

	auto get_scripting_class_name()
	{
		// Unity internal function
		// UnityEngine.MonoBehaviour::GetScriptClassName

		// *IMPORTANT : member function belongs to MonoBehaviour and NOT UnityEngine.Component

		auto temp_1 = address + 0xE0; // Unknown array

		auto scripting_class = memory_handler::read<uintptr_t>(temp_1 + 0x10); // Maybe scripting class

		auto scripting_class_2 = memory_handler::read<uintptr_t>(scripting_class + 0x8); // Maybe maybe

		auto name_address = memory_handler::read<uintptr_t>(scripting_class_2 + 0x48);

		return memory_handler::read_narrow_string(name_address);
	}
	
	static auto get_transform_from_component(const uintptr_t component_address) -> uintptr_t
	{
		// TODO - check this again the context is probably wrong
		// this offset chain might be correct only from game_object context
		
		auto attached_game_object = 
			memory_handler::read<uintptr_t>(component_address + offset::component::attached_game_object);

		if(!attached_game_object)
		{
			return 0;
		}
		
		auto t1 = memory_handler::read<uintptr_t>(attached_game_object + offset::game_object::component_array);

		auto t2 = memory_handler::read<uintptr_t>(t1 + 0x8);

		return memory_handler::read<uintptr_t>(t2 + 0x28);
	}

	static auto get_attached_components(const uintptr_t game_object)
	{
		auto component_array = 
			memory_handler::read<uintptr_t>(game_object + offset::game_object::component_array);

		auto count =
			memory_handler::read<uint64_t>(game_object + offset::game_object::component_count);

		auto last_component =
			memory_handler::read<uintptr_t>(component_array + 0x10 * count); // TODO - clean offset

		// TODO - finish this function
	}
};
