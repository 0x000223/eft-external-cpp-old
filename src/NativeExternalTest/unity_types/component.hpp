#pragma once
#include <cstdint>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "object.hpp"

class component : public object
{
	// Component
	// https://docs.unity3d.com/ScriptReference/Component.html

public:

	std::string class_name;

	std::string class_namespace;

	uintptr_t scripting_class;

	uintptr_t mono_class;
	
	uint16_t tag;

	uintptr_t transform;

	explicit component(const uintptr_t addr) : object(addr)
	{
		scripting_class = memory_handler::read<uintptr_t>(addr + offset::component::scripting_class);

		mono_class = memory_handler::read_chain(scripting_class, offset::component::mono_class);
		
		class_name = get_name();

		class_namespace = get_namespace();
	}
	
	auto get_name() const -> std::string
	{
		auto name_address = 
			memory_handler::read<uintptr_t>(mono_class + offset::mono::class_name);

		return memory_handler::read_narrow_string(name_address);
	}

	auto get_namespace() const -> std::string
	{
		auto namespace_address =
			memory_handler::read<uintptr_t>(mono_class + offset::mono::class_namespace);

		return memory_handler::read_narrow_string(namespace_address);
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
