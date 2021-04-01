#include "menu.hpp"

bool menu::show_menu		= false;

auto menu::set_menu_style() -> void
{
	auto& style = ImGui::GetStyle();

	style.FrameBorderSize	= 1.f;
	style.FrameRounding		= 3.f;
	style.GrabRounding		= 3.f;
	style.TabBorderSize		= 1.f;
	style.ScrollbarSize		= 3.f;
	style.WindowTitleAlign	= ImVec2(0.47f, 0.5f);

	
	style.Colors[ImGuiCol_Text]					= ImColor(17, 255, 164, 255);
	style.Colors[ImGuiCol_WindowBg]				= ImColor(15, 15, 15, 162);
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
	style.Colors[ImGuiCol_Button]				= ImColor(39, 40, 118, 102);
	style.Colors[ImGuiCol_CheckMark]			= ImColor(255, 0 ,118, 152);
	style.Colors[ImGuiCol_SliderGrab]			= ImColor(255, 0, 118, 152);
	style.Colors[ImGuiCol_ResizeGrip]			= ImColor(0, 0, 0, 42);
	style.Colors[ImGuiCol_Separator]			= ImColor(1, 0, 77, 128);
}

auto menu::main_menu_window() -> void
{
	ImGui::SetNextWindowSize(ImVec2(350.f, 400.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(1400.f, 350.f), ImGuiCond_Once);
	
	ImGui::Begin("External Utility - Pasted by 0x000223", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	if(ImGui::BeginTabBar("main_tab_bar"))
	{
		if(ImGui::BeginTabItem("Features"))
		{
			ImGui::BeginChild("features_child");

				{
					// Visuals - (health / box / snaplines / bones / loot / draw distance)

					// Color settings

					// Scripts - (recoil / stamina / aim)

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
			
			ImGui::EndTabItem();
		}
		
		if(ImGui::BeginTabItem("Settings"))
		{
			ImGui::ShowStyleEditor();
			
			ImGui::EndTabItem();
		}
		
		ImGui::EndTabBar();
	}
	
	ImGui::End();
}