#include "playerbody.hpp"
#include "utility.hpp"

using namespace std;

vector<transform> playerbody::parse_transforms() {

	vector<transform> ret;

	auto transforms_addr = memory::read<address_t>(m_skeleton_root_join_address + O_SKELETONROOTJOINT_VALUES);

	const auto count = memory::read<int>(transforms_addr + O_LIST_SIZE);
	const auto base = memory::read<address_t>(transforms_addr + O_LIST_ITEMS);

	for (auto& index : bone_indices) { // Parsing only the required transforms for an optimal skeleton
		const auto scripting_transform = memory::read<address_t>(base + O_ARRAY_BASE + index * 0x8);
		ret.push_back(transform(memory::read<address_t>(scripting_transform + 0x10))); // Cached ptr inside MonoBehaviour inherted classes - leads to UnityEngine::Component
	}

	return ret;
}
