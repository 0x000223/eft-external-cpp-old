/**
 * @file object.hpp
 * @date 12/02/2022
 * 
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "offset.hpp"
#include "memory.hpp"
#include "unity.hpp"

/**
 * @brief 
 */
enum ScriptingGHandleWeakness {
	GCHANDLE_INVALID = 0,
	GCHANDLE_WEAK = 1,
	GCHANDLE_STRONG = 2
};

/**
 * @brief Class which represents UnityEngine::Object
 * @see https://docs.unity3d.com/2018.4/Documentation/ScriptReference/Object.html
 */
class object
{
protected:
	
	/**
	 * @brief Address of Unity object
	 */
	const address_t m_address;

	/**
	 * @brief Unique instance id of Unity object
	 */
	const int m_instance_id;

	/**
	 * @brief 
	 */
	int64_t m_scripting_handle;

	/**
	 * @brief
	 */
	ScriptingGHandleWeakness m_scripting_handle_weakness;

	/**
	 * @brief Address of attached scripting backend object (C# classes which derive from 'MonoBehaviour')
	 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/MonoBehaviour.html
	 */
	address_t m_scripting_object;

	/**
	 * @brief
	 */
	address_t m_scripting_class;

	void set_scripting_object();

	void set_scripting_class();
	
	void set_scripting_class_name();
	
	void set_scripting_class_namespace();

public:

	/**
	 * @brief
	 */
	std::string m_scripting_class_name;

	/**
	 * @brief
	 */
	std::string m_scripting_class_namespace;

	object()
		: m_address(0), m_instance_id(0)
	{}
	
	explicit object(const address_t address)
		: m_address(address),
		m_instance_id(memory::read<int>(address + O_OBJECT_INSTANCEID))
	{}
};

#endif
