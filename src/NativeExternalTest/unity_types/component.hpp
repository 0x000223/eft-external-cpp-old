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
};
