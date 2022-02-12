#include "component.hpp"

using namespace std;

vector<component> component::get_components() const {

	if (m_game_object == 0) { // Not attached to any game object
		return vector<component>();
	}
	
	vector<component> components;

	const auto components_array = memory::read<address_t>(m_game_object + O_GAMEOBJECT_COMPONENT_ARRAY);
	const auto components_count = memory::read<int>(m_game_object + O_GAMEOBJECT_COMPONENT_SIZE);

	for (auto i = 0; i < components_count; ++i) {
		const auto address = memory::read<address_t>(components_array + 0x10 * i + 0x8);
		components.push_back( component(address) );
	}

	return components;
}
