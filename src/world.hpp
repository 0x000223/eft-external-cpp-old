/*****************************************************************//**
 * \file   world.hpp
 * \brief
 *
 * \author Max
 * \date   February 2022
 *********************************************************************/

#include <mutex>

#include "offset.hpp"
#include "memory.hpp"

#include "unity_types/game_object.hpp"
#include "unity_types/camera.hpp"
#include "scripting_types/player.hpp"

class world {

private :

	/**
	 * @brief GameObject which is attached to EFT.GameWorld Component
	 */
	static game_object attached_game_object;

	/**
	 * @brief Address of EFT.GameWorld instance
	 */
	static address_t scripting_object_address;

	/**
	 * @brief Check if there is an active instance of EFT.GameWorld
	 */
	static bool check_if_active();

	/**
	 * @brief Initialize data related to EFT.GameWorld instance
	 */
	static void initialize();

	/**
	 * @brief Destroy data related to EFT.GameWorld instance
	 */
	static void terminate();

	/**
	 * @brief
	 */
	static std::vector<player> get_player_list();

	/**
	 * @brief
	 */
	static player get_local_player();

public:

	/**
	 * @brief Indicates if there is an active instance of EFT.GameWorld
	 */
	static bool is_active;

	/**
	 * @brief
	 */
	static camera main_camera;

	/**
	 * @brief Local player of type EFT.Player
	 */
	static player local_player;

	/**
	 * @brief Registered players list of type EFT.Player
	 */
	static std::vector<player> players;

	/**
	 * @brief Update EFT.GameWorld instance state - via background task
	 */
	static void update_state();

	/**
	 * @brief Update player list
	 */
	static void update_players();
};