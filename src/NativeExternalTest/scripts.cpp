#include "scripts.hpp"

bool scripts::thermal_vision	= false;
bool scripts::night_vision		= false;
bool scripts::no_recoil			= false;

auto scripts::run_scripts() -> void
{
	// TODO
}

auto scripts::reset() -> void
{
	// TODO
}

auto scripts::toggle_thermal_vision() -> void
{
	auto main_camera = game_object::find_with_tag(5);

	auto thermal_component = main_camera->get_component_by_name("ThermalVision")->scripting_class;
	
	auto thermal_script = std::make_shared<ThermalVision>(thermal_component);

	thermal_script->toggle(thermal_vision);

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

	auto nvg_script = std::make_shared<NightVision>(nvg_component);

	nvg_script->toggle(night_vision);
}