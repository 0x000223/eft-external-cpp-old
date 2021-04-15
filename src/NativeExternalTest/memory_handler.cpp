#include "memory_handler.hpp"
#include "offset.hpp"

#pragma warning (disable : 26451)

unsigned long memory_handler::process_id = 0;

auto memory_handler::init() -> bool
{
	return bypass_handler::init();
}

auto memory_handler::terminate() -> void
{
	bypass_handler::terminate();
}

auto memory_handler::attach(const unsigned long proc_id) -> void
{
	process_id = proc_id;
}

auto memory_handler::read_bytes(const uintptr_t from, const size_t length) -> void*
{
	auto* buffer = malloc(length);
	
	bypass_handler::read_memory(process_id, reinterpret_cast<void*>(from), buffer, length);

	return buffer;
}

auto memory_handler::read_chain(const uintptr_t base, const std::vector<uintptr_t>& offsets) -> uintptr_t
{
	auto pointer = base;

	for(const auto& offset : offsets)
	{
		auto const temp_ptr = read<uintptr_t>(pointer + offset);

		pointer = temp_ptr;
	}

	return pointer;
}

auto memory_handler::read_narrow_string(const uintptr_t string_address) -> std::string
{
	if(string_address < 0x1000)
	{
		return std::string();
	}
	
	auto* buffer = static_cast<char*>(read_bytes(string_address, 265)); // Magic

	std::string ret;

	unsigned count = 0;
	
	while(buffer[count] != 0)
	{
		count++;
	}

	ret.assign(buffer, count);

	free(buffer);
	
	return ret;
}

auto memory_handler::read_wide_string(const uintptr_t string_address) -> std::wstring
{
	auto string_class = read<uintptr_t>(string_address);

	if(string_class < 0x1000 || string_class > 0x7FFFFFFFFFF)
	{
		return std::wstring();
	}
	
	auto length = read<int32_t>(string_class + offset::string::length);

	if(length < 0 || length > INT_MAX)
	{
		return std::wstring();
	}
	
	auto* buffer = read_bytes(string_class + offset::string::start, length * 2);

	if(!buffer)
	{
		return std::wstring();
	}
	
	auto ret = std::wstring().assign(static_cast<const wchar_t*>(buffer), length);

	free(buffer);

	return ret;
}

auto memory_handler::get_module_address(const wchar_t* module_name) -> uintptr_t
{
	return bypass_handler::get_module_address(process_id, module_name);
}