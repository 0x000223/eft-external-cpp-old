#include "physical.hpp"

void physical::set_legs_stamina(const float value) const {
	memory::write<float>(legs_stamina_address, value);
}

void physical::set_hands_stamina(const float value) const {
	memory::write<float>(hands_stamina_address, value);
}

void physical::set_oxygen(const float value) const {
	memory::write<float>(oxygen_address, value);
}