/**
 * @file component.hpp
 * @date 12/02/2022
 * 
 */

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "offset.hpp"
#include "memory.hpp"
#include "object.hpp"

/**
 * @brief Class which represents UnityEngine::Component
 * @see https://docs.unity3d.com/2019.4/Documentation/ScriptReference/Component.html
 */
class component : public object
{
protected:

	/**
	 * @brief Address of game object this component is attached to
	 */
	address_t m_game_object;

public:

	component()
		: object(0)
	{}
	
	explicit component(const address_t address)
		: object(address)
	{
		set_scripting_object();
		set_scripting_class();
		set_scripting_class_name();
		set_scripting_class_namespace();
	}
	
	/**
	 * @brief Returns all components of the game object this component is attached to
	 */
	std::vector<component> get_components() const;
};

#endif
