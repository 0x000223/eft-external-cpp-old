#include "scripts.hpp"

auto scripts::run_scripts() -> void
{
	if(settings::infinite_stamina)
	{
		unlimited_stamina();	
	}

	if(settings::no_recoil)
	{
		no_recoil();
	}

	if(settings::fov_aim) // TODO - refactor into settings structure with custom keybinds
	{
		if(GetAsyncKeyState(0x46) & 0x01) // 'F'
		{
			fov_aim();
		}
	}
}

auto scripts::reset() -> void
{
	// Run once upon enetering a new raid

}

auto scripts::toggle_thermal_vision() -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto thermal_component = main_camera.get_component_by_name("ThermalVision");
	
	auto thermal_script = std::make_shared<thermal_vision>(thermal_component.scripting_class);

	thermal_script->toggle(settings::thermal_vision);

	thermal_script->is_noisy(false);

	thermal_script->is_glitch(false);

	thermal_script->is_pixelated(false);

	thermal_script->is_motion_blurred(false);

	thermal_script->is_fps_stuck(false);
}

auto scripts::toggle_night_vision() -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto nvg_component = main_camera.get_component_by_name("NightVision");

	auto nvg_script = std::make_shared<night_vision>(nvg_component.scripting_class);

	nvg_script->toggle(settings::night_vision);
}

auto scripts::nvg_set_red(const float value) -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto nvg_component = main_camera.get_component_by_name("NightVision");

	auto nvg_script = std::make_shared<night_vision>(nvg_component.scripting_class);

	nvg_script->set_red(value);
}

auto scripts::nvg_set_green(const float value) -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto nvg_component = main_camera.get_component_by_name("NightVision");

	auto nvg_script = std::make_shared<night_vision>(nvg_component.scripting_class);

	nvg_script->set_green(value);
}

auto scripts::nvg_set_blue(const float value) -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto nvg_component = main_camera.get_component_by_name("NightVision");

	auto nvg_script = std::make_shared<night_vision>(nvg_component.scripting_class);

	nvg_script->set_blue(value);
}

auto scripts::toggle_no_visor() -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto visor_component = main_camera.get_component_by_name("VisorEffect");

	auto visor_script = std::make_unique<visor_effect>(visor_component.scripting_class);

	auto const value = settings::no_visor ? 0.f : 1.f;

	visor_script->set_intensity(value);
}

auto scripts::unlimited_stamina() -> void
{
	if(!raid_instance::local_player)
	{
		return;
	}
	
	raid_instance::local_player->physical->set_stamina(300.f);
	raid_instance::local_player->physical->set_hands_stamina(300.f);
	raid_instance::local_player->physical->set_oxygen(300.f);
}

auto scripts::no_recoil() -> void
{
	if(!raid_instance::local_player)
	{
		return;
	}

	raid_instance::local_player->procedural_wep_anim->set_shot_effector_strength( vector2(0,0) );
}

auto scripts::fov_aim() -> void
{
	if(!raid_instance::local_player)
	{
		return;
	}

	auto final_distance = 9999.f;
	auto final_angle = vector2();
	
	for(auto& player : raid_instance::players)
	{
		if(player == raid_instance::local_player)
		{
			continue;
		}

		auto const fireport_pos = 
			raid_instance::local_player->hands_controller->fireport->get_position();
		
		auto const target_angle = 
			vector3::calculate_angle(fireport_pos, player.body->bones->head.get_position());

		auto const distance = 
			raid_instance::local_player->movement_context->get_rotation().distance(target_angle);

		if(distance < settings::fov && distance < final_distance)
		{
			final_distance = distance;
			final_angle = target_angle;
		}
	}
	
	raid_instance::local_player->movement_context->set_rotation(final_angle);
}

auto scripts::find_closest_target() -> player
{
	if(!raid_instance::local_player)
	{
		return player (0);
	}

	auto const local_player_pos = raid_instance::local_player->body->bones->root.get_position();

	player ret (0);
	
	for(float distance = 10000; auto& player : raid_instance::players)
	{
		auto const temp_distance = player.body->bones->root.get_position().distance(local_player_pos);
		
		if(temp_distance < distance)
		{
			distance = temp_distance;

			ret = player;
		}
	}

	return ret;
}

auto scripts::test() -> void
{
	auto player_body = raid_instance::local_player->body->get_address();

	auto body_skins_dict = generic_dictionary<unsigned, uintptr_t>( memory_handler::read<uintptr_t>(player_body + 0x38) );

	auto test = body_skins_dict.entries;
}