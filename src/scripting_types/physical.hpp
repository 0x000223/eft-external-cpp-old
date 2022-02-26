
#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "offset.hpp"
#include "memory.hpp"

class physical {

private:

	/**
	 * @brief Address of this class instance
	 */
	address_t m_address;

	address_t legs_stamina_address;

	address_t hands_stamina_address;

	address_t oxygen_address;

public:

	physical()
		: m_address(0), legs_stamina_address(0), hands_stamina_address(0), oxygen_address(0)
	{}

	explicit physical(const address_t address)
		: m_address(address),
		legs_stamina_address(memory::read<address_t>(address + O_PHYSICAL_LEGSSTAMINA) + 0x48),
		hands_stamina_address(memory::read<address_t>(address + O_PHYSICAL_HANDSSTAMINS) + 0x48),
		oxygen_address(memory::read<address_t>(address + O_PHYSICAL_OXYGEN) + 0x48)
	{}

	void set_legs_stamina(const float value) const;

	void set_hands_stamina(const float value) const;

	void set_oxygen(const float value) const;
};

#endif