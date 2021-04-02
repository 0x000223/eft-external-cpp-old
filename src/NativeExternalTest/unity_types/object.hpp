#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "unity.hpp"

class object
{
	// Object
	// https://docs.unity3d.com/2018.4/Documentation/ScriptReference/Object.html

	// TODO
	// FindSceneObjectsOfType(MonoObject* ),
	// FindObjectsOfTypeIncludingAssets(MonoObject* ),
	// FindObjectsOfTypeImplementation
	// FindObjectFromInstanceID(int)
	// FindAllLiveObjects()
	// FindInstanceIDsOfTypeImplementation()
	// FindInstanceIDsOfType(Unity::Type, dynamic_array<int ,0> &, bool)
	// FindObjectOfType(),
	// FindObjectsOfType()
	
public:

	uintptr_t address;

	int instance_id;

	explicit object(const uintptr_t addr) : address(addr)
	{
		// TODO
	}

	virtual ~object();
	
	auto get_instance_id() const -> int
	{ 
		// TODO
		
		return 0;
	}

	auto set_hide_flags(const uint8_t hide_flags) const -> void
	{
		// Unity internal function
		
		auto bit_mask = memory_handler::read<uint32_t>(address + 0xC);

		bit_mask &= 0xFFF01FFF;

		bit_mask |= (hide_flags & 0x7F) << 13;

		memory_handler::write(address + 0xC, bit_mask);
	}
	
	auto get_type() const -> uintptr_t
	{
		// Unity internal function

		auto runtime_type_array = 
			memory_handler::read<uintptr_t>(process_state::module_address + offset::global::runtime_type_array);

		auto type_index = 
			memory_handler::read<uint32_t>(address + 0x3) >> 0x21;

		return memory_handler::read<uintptr_t>(runtime_type_array + type_index + 1); // Unity::Type
	}
	
	static auto find_objects_of_type(const uintptr_t unity_type)
	{
		auto type_to_object_set = 
			memory_handler::read<uintptr_t>(0x0 + process_state::module_address); // TODO - add type_to_object_set offset(!!!)

		// Get list of derived classes from target type
		auto derived_types = unity::find_all_derived_types(unity_type);

		// Check derived types count != 0

		// Parse each derived class
	}
};

inline object::~object()
{
	// TEST
}
