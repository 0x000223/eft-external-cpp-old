/**
 * @file memory.hpp
 * @date 14/02/2022
 * @brief
 * 
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>
#include <vector>

typedef unsigned long long address_t;

typedef unsigned long pid_t;


namespace process {

	/**
	 * @brief Process id of 'EscapeFromTarkov.exe'
	 */
	extern pid_t process_id;

	/**
	 * @brief Address of 'UnityPlayer.dll' module
	 */
	extern address_t module_address;

	/**
	 * @brief Returns target process id
	 */
	pid_t get_process_id(const std::string process_name);

	/**
	 * @brief Returns address of the requested module in attached process
	 */
	address_t get_module_address(const std::wstring module_name);
}

namespace memory {

	/**
	 * @brief Initializes memory connection - each with his own implementation
	 */
	bool init();

	/**
	 * @brief Terminates memory connection - each with his own implementation
	 */
	void terminate();
	
	/**
	 * @param Address to read from
	 */
	template<typename T>
	T read(const address_t address);

	/**
	 * @param Address to write to
	 * @param Data to write
	 */
	template<typename T>
	void write(const address_t address, T data);

	/**
	 * @param Address to read from
	 * @param Number of bytes to read
	 * @brief
	 */
	void* read_bytes(const address_t address, const size_t length);

	/**
	 * @param Starting address
	 * @param List of offsets to dereference from base
	 * @brief
	 */
	address_t read_chain(const address_t base, const std::vector<address_t>& offsets);
	
	/**
	 * @param Address of string
	 * @brief Reads UTF-8 string from a target address
	 */
	std::string read_narrow_string(const address_t address);

	/**
	 * @param Address of string
	 * @brief Reads unicode string from a target address
	 */
	std::wstring read_wide_string(const address_t address);
}

#endif