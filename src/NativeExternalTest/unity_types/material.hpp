#pragma once

#include "memory_handler.hpp"
#include "shader.hpp"
#include "color.hpp"

#pragma warning (disable : 26451)

class material
{
	// UnityEngine.Material
	// https://docs.unity3d.com/2018.4/Documentation/ScriptReference/Material.html

typedef uintptr_t retard_autist_clown;

private:

	uintptr_t address;

public:

	explicit material(const uintptr_t addr) : address(addr) {  }

	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_shader_property_sheet() const -> uintptr_t
	{
		auto const temp = memory_handler::read<uintptr_t>(address + 0xB0);

		return temp + 0x18;
	}
	
	auto has_property(const int fast_property_name) const -> bool
	{
		auto const v3 = memory_handler::read<uintptr_t>(address + 0xB0);

		auto const shader_property_sheet = v3 + 0x18;

		// ShaderPropertySheet::HasProperty(*this, fast_property_name)

		auto const v2 = memory_handler::read<uintptr_t>(shader_property_sheet + 0x38); // Last property ?

		if(!v2)
		{
			return false;
		}

		uintptr_t counter = 0;
		
		for(auto i = memory_handler::read<uintptr_t>(shader_property_sheet + 0x28); 
			memory_handler::read<int32_t>(i) != fast_property_name; 
			i += 0x8)
		{
			if(++counter == v2)
			{
				return false;
			}
		}

		return true;
	}

	auto get_float_value_in_rgb_space(const int property_index)
	{
		auto shader_property_sheet = get_shader_property_sheet();

		auto index_array = memory_handler::read<uintptr_t>(shader_property_sheet + 0x48);

		auto v2 = memory_handler::read<unsigned>(index_array + 4 * property_index);

		auto v3 = memory_handler::read<uintptr_t>(shader_property_sheet + 0x68);

		auto v4 = v2 & 0xFFFFF;

		if( (v2 & 0x40000000) != 0 )
		{
			auto result = memory_handler::read<unsigned>(v4 + v3);
			
			if(get_active_color_space() == 1)
			{
				//LinearToGammaSpace
			}
		}
	}

	auto get_active_color_space() const -> unsigned
	{
		if(!managers::get_manager_from_context(0))
		{
			return 0xFFFFFFFF;
		}

		auto const player_settings = managers::get_manager_from_context(0);

		return memory_handler::read<unsigned>(player_settings + 0x25C);	
	}

	auto linear_to_gamma_space()
	{
		
	}
	
	auto get_color() const -> color
	{
		auto v3 = memory_handler::read<uintptr_t>(address + 0xB0);

		auto shader_property_sheet = v3 + 0x18;

		auto property_index = memory_handler::read<int>(v3 + 0x2C);

		auto v8 = memory_handler::read<int>(v3 + 0x30);

		auto fast_name_array = memory_handler::read<uintptr_t>(shader_property_sheet + 0x28);
		
		if(property_index > v8)
		{
			return color();
		}

		while(property_index < v8) // Iterating properties up to '_Color'
		{
			// Iterating shader property names

			auto temp_fast_name = memory_handler::read<int>(fast_name_array + 0x4 * property_index);

			auto property_name = shader::get_property_name(temp_fast_name);

			if(property_name == "_Color")
			{
				// ShaderPropertySheet::GetVectorValueInsRGBSpace

				auto unk = memory_handler::read<uintptr_t>(shader_property_sheet + 0x68);

				auto index_array = memory_handler::read<uintptr_t>(shader_property_sheet + 0x48);
				
				auto unk2 = memory_handler::read<unsigned>(index_array + 0x4 * property_index);

				auto color_address = unk + (unk2 + 0xFFFFF);

				if((unk2 & 0x40000000) != 0)
				{
					
				}
				
				return color( color_address );
			}
			
			if(property_index > v8)
			{
				return color();
			}

			property_index += 1;
		}

		return color();
	}
};