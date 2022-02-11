#pragma once

struct settings
{
	// Camera related
	static bool thermal_vision;
	static bool night_vision;
	static bool no_visor;

	static float nvg_color_red;
	static float nvg_color_green;
	static float nvg_color_blue;
	
	// Character related
	static bool no_recoil;
	static bool infinite_stamina;

	static bool fov_aim;
	static float fov;
	
	// Rendering related
	static float player_draw_distance;
	static float corpse_draw_distance;
	static float item_draw_distance;
	
	static bool player_name;
	static bool player_health;
	static bool player_faction;
	static bool player_distance;
	static bool player_bones;
	static bool player_snapline;
	static bool player_box;
};