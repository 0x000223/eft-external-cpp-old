#include "game_object.hpp"

using namespace std;

address_t g_GOM = 0;

address_t game_object::get_transform() const {
	
	return memory::read<address_t>(m_component_array + 0x10 * 0 + 0x8); // Transform is always the first component - hence index '0'
}

component& game_object::get_component_by_name(const string name) const { 

	auto ret = component();

	for (auto i = 0; i < m_component_count; ++i) {
		auto ret = component(memory::read<address_t>(m_component_array + 0x10 * i + 0x8));

		if (ret.m_scripting_class_name.find(name) != std::string::npos) {
			return ret;
		}
	}

	return ret;
}

vector<component>& game_object::get_components() const {

	vector<component> components;

	for (auto i = 0; i < m_component_count; ++i) {
		components.emplace_back(memory::read<address_t>(m_component_array + 0x10 * i + 0x8));
	}

	return components;
}

vector<game_object>& game_object::get_active_objects(size_t limit) {

	vector<game_object> active_objects;

	if (g_GOM == 0) {
		return active_objects;
	}

	auto active_node = memory::read<address_t>(g_GOM + O_GOM_ACTIVE_NODES);

	if (active_node == memory::read<address_t>(active_node + O_GOM_NODE_NEXT)) { // No active nodes
		return active_objects;
	}

	auto first_node = active_node;
	auto count = 0;

	while (true) {

		const auto node_data = memory::read<address_t>(active_node + O_GOM_NODE_DATA);

		active_objects.push_back(game_object(node_data));
		active_node = memory::read<address_t>(active_node + O_GOM_NODE_NEXT);

		++count;

		if (active_node == first_node || limit == count) {
			break;
		}
	}

	return active_objects;
}

vector<game_object>& game_object::get_tagged_objects() {

	vector<game_object> tagged_objects;

	if (g_GOM == 0) {
		return tagged_objects;
	}

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

game_object game_object::find(const std::string name) {

	if (g_GOM == 0) {
		return game_object();
	}

	// Iterate active nodes
	auto active_node = memory::read<address_t>(g_GOM + O_GOM_ACTIVE_NODES);

	if (active_node != memory::read<address_t>(active_node + O_GOM_NODE_NEXT)) { // Check if there are active nodes
		const auto first_node = active_node;
		while (true) {
			const auto node_data = memory::read<address_t>(active_node + O_GOM_NODE_DATA);
			const auto current = game_object(node_data);
			
			if (current.m_name.find(name) != string::npos) { // Check GameObject for matching name
				return current;
			}

			active_node = memory::read<address_t>(active_node + O_GOM_NODE_NEXT);
			if (active_node == first_node) { // No more active nodes
				break;
			}
		}
	}

	// Iterate tagged nodes
	auto tagged_node = memory::read<address_t>(g_GOM + O_GOM_TAGGED_NODES);

	while (tagged_node != g_GOM) {
		const auto node_data = memory::read<address_t>(g_GOM + O_GOM_NODE_DATA);
		const auto current = game_object(node_data);

		if (current.m_name.find(name) != string::npos) { // Check GameObjet for matching name
			return current;
		}

		tagged_node = memory::read<address_t>(tagged_node + O_GOM_NODE_NEXT);
	}

	return game_object();
}

game_object game_object::find_main_camera() {
	if (g_GOM == 0) {
		return game_object();
	}

	const auto camera_tagged_node = memory::read<address_t>(g_GOM + O_GOM_MAINCAMERA_TAGGED_NODES);

	if (camera_tagged_node == memory::read<address_t>(camera_tagged_node + O_GOM_NODE_NEXT)) { // No camera tagged nodes
		return game_object();
	}

	auto camera_node = camera_tagged_node;

	while (true) {

		const auto node_data = memory::read<address_t>(camera_node + O_GOM_NODE_DATA);
		const auto current = game_object(node_data);

		if (current.m_name == "FPS Camera") {
			return current;
		}

		camera_node = memory::read<address_t>(camera_node + O_GOM_NODE_NEXT);
		if (camera_node == camera_tagged_node) {
			break;
		}
	}

	return game_object();
}
