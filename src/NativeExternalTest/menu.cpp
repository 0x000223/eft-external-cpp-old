#include "menu.hpp"

bool menu::show_menu = false;

float	menu::settings::float_player_distance	= 300.f;
bool	menu::settings::player_box				= false;
bool	menu::settings::player_snapline			= false;
bool	menu::settings::player_name				= true;
bool	menu::settings::player_health			= true;
bool	menu::settings::player_faction			= false;
bool	menu::settings::player_distance			= false;
bool	menu::settings::player_bones			= true;

auto menu::menu_style_default() -> void
{
	auto& style = ImGui::GetStyle();

	style.FrameBorderSize	= 1.f;
	style.FrameRounding		= 0.f;
	style.FramePadding		= ImVec2(4.f, 0.f);
	style.GrabRounding		= 3.f;
	style.TabRounding		= 0.f;
	style.TabBorderSize		= 1.f;
	style.ScrollbarSize		= 3.f;
	
	style.Colors[ImGuiCol_Text]					= ImColor(135, 255, 212, 255);
	style.Colors[ImGuiCol_WindowBg]				= ImColor(15, 15, 15, 220);
	style.Colors[ImGuiCol_TitleBgActive]		= ImColor(18, 7, 37, 255);
	style.Colors[ImGuiCol_Border]				= ImColor(0, 0, 0, 255);
	style.Colors[ImGuiCol_Tab]					= ImColor(45, 20, 63, 255);
	style.Colors[ImGuiCol_TabHovered]			= ImColor(113, 10, 102, 189);
	style.Colors[ImGuiCol_TabActive]			= ImColor(169, 49, 132, 235);
	style.Colors[ImGuiCol_FrameBg]				= ImColor(28 ,96, 100, 62);
	style.Colors[ImGuiCol_FrameBgHovered]		= ImColor(52, 117, 94, 102);
	style.Colors[ImGuiCol_FrameBgActive]		= ImColor(42, 172, 53, 171);
	style.Colors[ImGuiCol_ScrollbarGrab]		= ImColor(48, 12, 36, 255);
	style.Colors[ImGuiCol_ScrollbarGrabHovered]	= ImColor(113, 4 ,76, 255);
	style.Colors[ImGuiCol_Button]				= ImColor(89, 91, 137, 102);
	style.Colors[ImGuiCol_ButtonHovered]		= ImColor(56, 78, 103, 255);
	style.Colors[ImGuiCol_CheckMark]			= ImColor(255, 0 ,118, 152);
	style.Colors[ImGuiCol_SliderGrab]			= ImColor(255, 0, 118, 152);
	style.Colors[ImGuiCol_ResizeGrip]			= ImColor(0, 0, 0, 42);
	style.Colors[ImGuiCol_Separator]			= ImColor(1, 0, 77, 128);
}

auto menu::main_window() -> void
{
	static auto tab_window = 0;
	static auto button_size = ImVec2(146.f, 30.f);
	
	ImGui::SetNextWindowSize(ImVec2(600.f, 400.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(1100.f, 350.f), ImGuiCond_Once);
	
	ImGui::Begin("External Utility - Pasted by 0x000223", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if(ImGui::Button("Features", button_size))
	{
		// Visuals child window
		tab_window = 0;
	}

	ImGui::SameLine(0.f, 0.0f);
	
	if(ImGui::Button("Aim", button_size))
	{
		// Aim child window
		tab_window = 1;
	}

	ImGui::SameLine(0.f, 0.0f);

	if(ImGui::Button("Data", button_size))
	{
		// Data child window
		tab_window = 2;
	}

	ImGui::SameLine(0.f, 0.0f);
	
	if(ImGui::Button("Settings", button_size))
	{
		// Settings child window
		tab_window = 3;
	}

	switch (tab_window)
	{
	case 0:
		visuals_tab_window();
		break;

	case 1:
		aim_tab_window();
		break;

	case 2:
		data_tab_window();
		break;
		
	default: ;
		ImGui::ShowStyleEditor();
		break;
	}
	
	ImGui::End();
}

auto menu::visuals_tab_window() -> void
{
	ImGui::BeginChild("visuals_child_window", ImVec2(0,0), true, ImGuiWindowFlags_ChildWindow);

		ImGui::BeginChild("esp_child_window", ImVec2(500.f, 170.f), true, ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoScrollbar);

		{
			ImGui::Text("Player Draw Distance");
			
			ImGui::SliderFloat("", &settings::float_player_distance, 0.f, 2000.f);

			ImGui::Checkbox("Name", &settings::player_name);

			ImGui::Checkbox("Health", &settings::player_health);

			ImGui::Checkbox("Distance", &settings::player_distance);
		
			ImGui::Checkbox("Faction", &settings::player_faction);

			ImGui::Checkbox("Bones", &settings::player_bones);
		
			ImGui::Checkbox("Snapline", &settings::player_snapline);

			ImGui::Checkbox("Box", &settings::player_box);
		}
	
		ImGui::EndChild();
	
		ImGui::BeginChild("camera_child_window", ImVec2(245.f,60.f), true, ImGuiWindowFlags_ChildWindow);

		{
			if(ImGui::Checkbox("Thermal Vision", &scripts::flags::thermal_vision))
			{
				scripts::toggle_thermal_vision();
			}

			if(ImGui::Checkbox("Night Vision", &scripts::flags::night_vision))
			{
				scripts::toggle_night_vision();
			}
		}
		
		ImGui::EndChild();

		ImGui::SameLine(0.f, 10.f);
	
		ImGui::BeginChild("character_child_window", ImVec2(245.f, 60.f), true, ImGuiWindowFlags_ChildWindow);

		{
			ImGui::Checkbox("Stamina", &scripts::flags::unlimited_stamina);

			ImGui::Checkbox("No Recoil", &scripts::flags::no_recoil);
		}
	
		ImGui::EndChild();

		if(ImGui::Button("TEST"))
		{
			scripts::test();
		}
		
	ImGui::EndChild();
}

auto menu::aim_tab_window() -> void
{
	ImGui::BeginChild("aim_child_window", ImVec2(0,0), ImGuiWindowFlags_ChildWindow);

	ImGui::Checkbox("FOV Aimbot", &scripts::flags::fov_aim);

	ImGui::Text("FOV");

	ImGui::SliderFloat("", &scripts::flags::fov, 1.f, 2000.f);
	
	ImGui::EndChild();
}

auto menu::data_tab_window() -> void
{
	ImGui::BeginChild("data_child_window", ImVec2(0,0), ImGuiWindowFlags_ChildWindow);

		ImGui::BeginChild("object_inspector_child_window");

		static bool active_objects_window = false;

		static bool tagged_objects_window = false;
	
		static std::vector<game_object> active_objects;

		static std::vector<game_object> tagged_objects;
	
		if(ImGui::Button("Active Objects", ImVec2(120.f, 25.f)))
		{
			active_objects_window = !active_objects_window;
			
			active_objects = game_object::get_active_objects();
		}

		if(ImGui::Button("Tagged Objects", ImVec2(120.f, 25.f)))
		{
			tagged_objects_window = !tagged_objects_window;

			tagged_objects = game_object::get_tagged_objects();
		}
	
		if(active_objects_window)
		{
			ImGui::Begin("Active Objects");

			for(const auto& object : active_objects)
			{
				if( ImGui::TreeNodeEx(object.name.c_str()) )
				{
					auto components = object.get_all_components();

					for(const auto& component : components)
					{
						ImGui::TextColored(ImColor(255,50,50,255), "0x%llX", component.get_address());
						ImGui::TextColored(ImColor(60,255,60,255) ,"%s", component.class_name.c_str());
						ImGui::TextColored(ImColor(60,60,255,255), "0x%llX", component.scripting_class);
						ImGui::Separator();
					}
					
					ImGui::TreePop();
				}
			}
			
			ImGui::End();
		}

		if(tagged_objects_window)
		{
			ImGui::Begin("Tagged Objects");

			for(const auto& object : tagged_objects)
			{
				if( ImGui::TreeNodeEx(object.name.c_str()) )
				{
					auto components = object.get_all_components();

					for(const auto& component : components)
					{
						ImGui::TextColored(ImColor(255,50,50,255), "0x%llX", component.get_address());
						ImGui::TextColored(ImColor(60,255,60,255) ,"%s", component.class_name.c_str());
						ImGui::TextColored(ImColor(60,60,255,255), "0x%llX", component.scripting_class);
						ImGui::Separator();
					}
					
					ImGui::TreePop();
				}
			}
			
			ImGui::End();
		}
	
		ImGui::EndChild();
	
	ImGui::EndChild();
}
