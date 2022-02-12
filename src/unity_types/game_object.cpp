#include "game_object.hpp"

using namespace std;

address_t g_GOM = 0;

address_t game_object::get_transform() const {
	
	return memory::read<address_t>(m_component_array + 0x10 * 0 + 0x8); // Transform is always the first component - hence index '0'
}

component game_object::get_component_by_name(const string component_name) const { 

	for (auto i = 0; i < m_component_count; ++i) {
		const auto current = component(memory::read<address_t>(m_component_array + 0x10 * i + 0x8));

		if (current.m_scripting_class_name.find(component_name) != std::string::npos) {
			return current;
		}
	}

	return component();
}

vector<component> game_object::get_components() const {

	vector<component> components;

	for (auto i = 0; i < m_component_count; ++i) {
		components.emplace_back(memory::read<address_t>(m_component_array + 0x10 * i + 0x8));
	}

	return components;
}

vector<game_object> game_object::get_active_objects() {

	if (g_GOM == 0) {
		return vector<game_object>();
	}

	vector<game_object> active_objects;

	auto active_node = memory::read<address_t>(g_GOM + O_GOM_ACTIVE_NODES);

	if (active_node == memory::read<address_t>(active_node + O_GOM_NODE_NEXT)) { // No active nodes
		return vector<game_object>();
	}

	auto first_node = active_node;

	while (true) {

		const auto node_data = memory::read<address_t>(active_node + O_GOM_NODE_DATA);

		active_objects.push_back(game_object(node_data));
		active_node = memory::read<address_t>(active_node + O_GOM_NODE_NEXT);

		if (active_node == first_node) {
			break;
		}
	}

	return active_objects;
}

vector<game_object> game_object::get_tagged_objects() {

	if (g_GOM == 0) {
		return vector<game_object>();
	}

	vector<game_object> tagged_objects;

	auto tagged_node = memory::read<address_t>(g_GOM + O_GOM_TAGGED_NODES);

	while (tagged_node != g_GOM) {

		const auto node_data = memory::read<address_t>(tagged_node + O_GOM_NODE_DATA);

		tagged_objects.push_back(game_object(node_data));

		tagged_node = memory::read<address_t>(tagged_node + O_GOM_NODE_NEXT);
	}

	return tagged_objects;
}

vector<game_object> game_object::find_game_objects_with_tag(const uint16_t tag) {

	if (g_GOM == 0) {
		return vector<game_object>();
	}

	vector<game_object> tagged_objects;

	auto tagged_node = memory::read<address_t>(g_GOM + O_GOM_TAGGED_NODES);

	while (tagged_node != g_GOM) {

		const auto node_data = memory::read<address_t>(tagged_node + O_GOM_NODE_DATA);
		const auto current = game_object(node_data);

		if (current.m_tag == tag) {
			tagged_objects.push_back(current);
		}

		tagged_node = memory::read<address_t>(tagged_node + O_GOM_NODE_NEXT);
	}

	return tagged_objects;
}

game_object game_object::find_with_tag(const uint16_t tag) { 

	if (g_GOM == 0) {
		return game_object();
	}

	auto tagged_node = memory::read<address_t>(g_GOM + O_GOM_TAGGED_NODES);

	if (tagged_node == g_GOM) { // No tagged nodes
		return game_object();
	}

	while (tagged_node != g_GOM)
	{
		const auto node_data = memory::read<address_t>(tagged_node + O_GOM_NODE_DATA);
		const auto current = game_object(node_data);

		if (current.m_tag == tag) {
			return current;
		}

		tagged_node = memory::read<address_t>(tagged_node + O_GOM_NODE_NEXT);
	}

	return game_object();
}
