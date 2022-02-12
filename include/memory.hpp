/**
 * @file memory_handler.hpp
 * @author Max Penkov
 * @date 11/02/2022
 * @brief
 * 
 */

#ifndef MEMORY_HANDLER_HPP
#define MEMORY_HANDLER_HPP

#include <string>
#include <vector>

typedef unsigned long long address_t;

typedef unsigned long pid_t;

namespace memory {
	/**
	 * @brief Process id of 'EscapeFromTarkov.exe'
	 */
	static pid_t process_id;

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
	address_t read_chain(address_t base, const std::vector<address_t>& offsets);
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

namespace process {
	/**
	 * @brief Address of 'UnityPlayer.dll' module
	 */
	static address_t module_addres;

	/**
	 * @brief Returns target process id
	 */
	pid_t get_process_id(const std::string process_name);

	/**
	 * @brief Returns address of the requested module in attached process
	 */
	address_t get_module_address(const std::wstring module_name);
}

#endif