#pragma once

#include "offset.hpp"
#include "memory_handler.hpp"
#include "process_state.hpp"
#include "unity.hpp"

#pragma warning (disable : 26451)

class shader
{
	// UnityEngine.Shader
	// https://docs.unity3d.com/ScriptReference/Shader.html

	// FindPropertyIndex()
	// GetPropertyAttributes()
	// GetPropertyCount()
	// GetPropertyDescription
	// GetPropertyFlags()
	// GetPropertyNameId()
	// GetPropertyType()
	// Find(string name)

private:

	uintptr_t address;
	
public:

	explicit shader(const uintptr_t addr) : address(addr) {  }

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto test_get_color() const -> void
	{
		if(!memory_handler::read<uintptr_t>(address + 0x38))
		{
			return;
		}

		auto v5 = memory_handler::read<int>(address + 0x14);
		auto v6 = memory_handler::read<int>(address + 0x18);

		auto v8 = memory_handler::read<uintptr_t>(address + 0x28);
		
	}

	static auto get_property_name(const int fast_property_name) -> std::string
	{
		// ShaderLab::FastPropertyName::GetName
		
		auto unk = process_state::module_address + 0x1517F30; // 0x1516F30 - default string ?

		auto test = process_state::module_address + 0x12B1170;
		
		auto v1 = memory_handler::read_narrow_string( memory_handler::read<uintptr_t>(unk) );

		if(fast_property_name == -1)
		{
			return v1;
		}

		auto const v4 = fast_property_name & 0xC0000000;

		if( (fast_property_name & 0xC0000000) == 0x80000000)
		{
			return unity::get_built_in_matrix_param_name(fast_property_name & 0x3FFFFFFF);
		}

		if(v4 == 0xC0000000)
		{
			return unity::get_built_in_text_env_param_name(fast_property_name & 0x3FFFFFFF);
		}

		if(v4 != 0x40000000)
		{
			auto unk2 = memory_handler::read<uintptr_t>( process_state::module_address + 0x15B3198 );
			
			if(fast_property_name >= 0 && fast_property_name < memory_handler::read<int>(unk2 + 0x10))
			{
				auto temp = memory_handler::read<uintptr_t>(memory_handler::read<uintptr_t>(unk2) + 0x8 * fast_property_name);

				v1 = memory_handler::read_narrow_string(temp);
			}

			return v1;
		}

		return unity::get_built_in_vector_param_name(fast_property_name & 0x3FFFFFFF);
	}
};