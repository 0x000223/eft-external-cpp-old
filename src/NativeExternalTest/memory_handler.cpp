#include "memory_handler.hpp"

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

auto memory_handler::read_narrow_string(const uintptr_t string_address) -> std::string
{
	auto* buffer = static_cast<char*>(read_bytes(string_address, 265)); // Magic

	std::string ret;

	unsigned count = 0;
	
	while(buffer[count] != 0)
	{
		count++;
	}

	ret.assign(buffer, count);

	return ret;
}

auto memory_handler::get_module_address(const wchar_t* module_name) -> uintptr_t
{
	return bypass_handler::get_module_address(process_id, module_name);
}