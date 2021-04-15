#pragma once
#include <vector>

#include "offset.hpp"
#include "memory_handler.hpp"

template<typename TKey, typename TValue>
class generic_dictionary
{
	// System.Collections.Generic.Dictionary<TKey, TValue>
	
private:
	
	uintptr_t address;

	int count;

	int free_count;

	template<typename TKey, typename TValue>
	struct entry
	{
	private:

		uintptr_t address;

	public:
		
		int hash_code;

		int next;

		TKey key;

		TValue value;

		entry() = default;
		
		explicit entry(const uintptr_t addr) : address(addr)
		{
			hash_code =
				memory_handler::read<int>(address + 0x0);

			next =
				memory_handler::read<int>(address + 0x4);

			key =
				memory_handler::read<TKey>(address + 0x8);

			value =
				memory_handler::read<TValue>(address + 0x10);
		}
	};
	
public:

	std::vector<entry<TKey, TValue>> entries;

	generic_dictionary() = default;
	
	explicit generic_dictionary(const uintptr_t addr) : address(addr)
	{
		count =
			memory_handler::read<uint32_t>(address + offset::generic_dictionary::count);

		free_count =
			memory_handler::read<int>(address + offset::generic_dictionary::free_count);

		auto entries_array = 
			memory_handler::read<uintptr_t>(address + offset::generic_dictionary::entries_array);

		auto entries_count = 
			memory_handler::read<int>(entries_array + offset::array::count);

		if(count > 5000) // TODO - temp bandaid fix
		{
			return;
		}
		
		for(auto index = 0; index < count; ++index)
		{
			auto entry_addr = 
					entries_array + offset::array::base + (index * 0x18);

			entries.push_back( entry<TKey, TValue>(entry_addr) );
		}
	}

	auto get_count() const -> int
	{
		return count - free_count;
	}
};