/**
 * @file game_object_hpp
 * @date 12/02/2022
 * @brief
 * 
 */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "object.hpp"
#include "component.hpp"

/**
 * @brief Address of GameObjectManager
 */
extern address_t g_GOM;

/**
 * @brief Class which represents UnityEngine::GameObject 
 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/GameObject.html
 */
class game_object : public object
{
private:

	/**
	 * @brief Address of attached components array
	 */
	address_t m_component_array;

	/**
	 * @brief Number of attached components
	 */
	uint64_t m_component_count;

	/**
	 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/GameObject-transform.html
	 */
	address_t get_transform() const;

protected:
	

public:

	/**
	 * @brief Used to identify a GameObject
	 */
	uint16_t m_tag;

	/**
	 * @brief Name of the GameObject
	 */
	std::string m_name;

	/**
	 * @brief Address of the attached transform component
	 */
	address_t m_transform;

	game_object()
		: object(), m_tag(0), m_name(""), m_transform(0), m_component_array(0), m_component_count(0)
	{}

	game_object(address_t address)
		: object(address),
		m_component_array(memory::read<address_t>(m_address + O_GAMEOBJECT_COMPONENT_ARRAY)),
		m_component_count(memory::read<uint64_t>(m_address + O_GAMEOBJECT_COMPONENT_SIZE)),
		m_name(memory::read_narrow_string(m_address + O_GAMEOBJECT_NAME)),
		m_tag(memory::read<uint16_t>(m_address + O_GAMEOBJECT_TAG)),
		m_transform(get_transform())
	{}

	/**
	 * @brief
	 */
	component get_component_by_name(const std::string name) const;

	/**
	 * @brief Retruns all components which are attached to this GameObject
	 */
	std::vector<component> get_components() const;
	
	/**
	 * @brief Returns all active GameObjects
	 * @param Maximum limit of how many active GameObjects to return
	 */
	static std::vector<game_object> get_active_objects(std::size_t limit = 0);
	
	/**
	 * @brief Returns all tagged GameObjects
	 */
	static std::vector<game_object> get_tagged_objects();

	/**
	 * @brief Returns an array of active GameObjects
	 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/GameObject.FindGameObjectsWithTag.html
	 */
	static std::vector<game_object> find_game_objects_with_tag(const uint16_t tag);
	
	/**
	 * @brief Returns single active GameObject
	 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/GameObject.FindWithTag.html
	 */
	static game_object find_with_tag(const uint16_t tag);

	/**
	 * @brief Returns first GameObject with a matching name
	 */
	static game_object find(const std::string name);

	/**
	 * @brief Returns main camera GameObject
	 */
	static game_object find_main_camera();
};

#endif
