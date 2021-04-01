#include "scripts.hpp"

bool scripts::flags::thermal_vision		= false;
bool scripts::flags::night_vision		= false;
bool scripts::flags::no_recoil			= false;
bool scripts::flags::unlimited_stamina	= false;

auto scripts::run_scripts() -> void
{
	if(flags::unlimited_stamina)
	{
		unlimited_stamina();	
	}
}

auto scripts::reset() -> void
{
	// TODO
}

auto scripts::toggle_thermal_vision() -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto thermal_component = main_camera->get_component_by_name("ThermalVision")->scripting_class;
	
	auto thermal_script = std::make_shared<thermal_vision>(thermal_component);

	thermal_script->toggle(flags::thermal_vision);

	thermal_script->is_noisy(false);

	thermal_script->is_glitch(false);

	thermal_script->is_pixelated(false);

	thermal_script->is_motion_blurred(false);

	thermal_script->is_fps_stuck(false);
}

auto scripts::toggle_night_vision() -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto nvg_component = main_camera->get_component_by_name("NightVision")->scripting_class;

	auto nvg_script = std::make_shared<night_vision>(nvg_component);

	nvg_script->toggle(flags::night_vision);
}

auto scripts::unlimited_stamina() -> void
{
	if(!raid_instance::local_player)
	{
		return;
	}
	
	auto physical = raid_instance::local_player->physical;

	physical->set_stamina(300.f);
	physical->set_hands_stamina(300.f);
	physical->set_oxygen(300.f);
}