#include "render.hpp"

#include "render_backend.hpp"
#include "feature.hpp"
using namespace std;

//ImFont*	render::font_mbender			= nullptr;
//ImFont*	render::font_mbender_bold		= nullptr;

void render::menu_set_style_default() {

	auto& style = ImGui::GetStyle();

	style.FrameBorderSize = 1.f;
	style.FrameRounding = 0.f;
	style.FramePadding = ImVec2(4.f, 0.f);
	style.GrabRounding = 3.f;
	style.TabRounding = 0.f;
	style.TabBorderSize = 1.f;
	style.ScrollbarSize = 3.f;

	style.Colors[ImGuiCol_Text] = ImColor(135, 255, 212, 255);
	style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 220);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(18, 7, 37, 255);
	style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
	style.Colors[ImGuiCol_Tab] = ImColor(45, 20, 63, 255);
	style.Colors[ImGuiCol_TabHovered] = ImColor(113, 10, 102, 189);
	style.Colors[ImGuiCol_TabActive] = ImColor(169, 49, 132, 235);
	style.Colors[ImGuiCol_FrameBg] = ImColor(28, 96, 100, 62);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(52, 117, 94, 102);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(42, 172, 53, 171);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(48, 12, 36, 255);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(113, 4, 76, 255);
	style.Colors[ImGuiCol_Button] = ImColor(89, 91, 137, 102);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(56, 78, 103, 255);
	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 118, 152);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 118, 152);
	style.Colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 42);
	style.Colors[ImGuiCol_Separator] = ImColor(1, 0, 77, 128);
}

static void render::menu_window_main() {

	static auto tab_window = 0;
	static auto button_size = ImVec2(146.f, 30.f);

	ImGui::SetNextWindowSize(ImVec2(600.f, 400.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(1100.f, 350.f), ImGuiCond_Once);

	ImGui::Begin("eft-external-cpp", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	if (ImGui::Button("Features", button_size))
	{
		// Visuals child window
		tab_window = 0;
	}

	ImGui::SameLine(0.f, 0.0f);

	if (ImGui::Button("Aim", button_size))
	{
		// Aim child window
		tab_window = 1;
	}

	ImGui::SameLine(0.f, 0.0f);

	if (ImGui::Button("Data", button_size))
	{
		// Data child window
		tab_window = 2;
	}

	ImGui::SameLine(0.f, 0.0f);

	if (ImGui::Button("Settings", button_size))
	{
		// Settings child window
		tab_window = 3;
	}

	switch (tab_window)
	{
	case 0:
		//menu_tab_visual();
		break;

	case 1:
		//menu_tab_aim();
		break;

	default:;
		ImGui::ShowStyleEditor();
		break;
	}

	ImGui::End();
}

//static void render::menu_tab_visual() {
//
//	ImGui::BeginChild("visuals_child_window", ImVec2(0, 0), true, ImGuiWindowFlags_ChildWindow);
//
//	ImGui::TextColored(ImVec4(255, 255, 255, 255), "Visuals");
//
//	{
//		ImGui::Text("Player Draw Distance");
//
//		ImGui::SliderFloat("", &settings::player_draw_distance, 0.f, 2000.f);
//
//		ImGui::Checkbox("Name", &settings::player_name);
//
//		ImGui::Checkbox("Health", &settings::player_health);
//
//		ImGui::Checkbox("Distance", &settings::player_distance);
//
//		ImGui::Checkbox("Faction", &settings::player_faction);
//
//		ImGui::Checkbox("Bones", &settings::player_bones);
//
//		ImGui::Checkbox("Snapline", &settings::player_snapline);
//
//		ImGui::Checkbox("Box", &settings::player_box);
//	}
//
//	ImGui::TextColored(ImVec4(255, 255, 255, 255), "Camera");
//
//	{
//		if (ImGui::Checkbox("Night Vision", &settings::night_vision))
//		{
//			// Toggle NVG
//		}
//
//		if (ImGui::Checkbox("Thermal Vision", &settings::thermal_vision))
//		{
//			// Toggle thermal vision
//		}
//
//		if (ImGui::Checkbox("No Visor", &settings::no_visor))
//		{
//			// Toggle no visor
//		}
//	}
//
//	ImGui::TextColored(ImVec4(255, 255, 255, 255), "Misc");
//
//	{
//		ImGui::Checkbox("Stamina", &settings::infinite_stamina);
//
//		ImGui::Checkbox("No Recoil", &settings::no_recoil);
//	}
//
//	ImGui::EndChild();
//}
//
//static void render::menu_tab_aim() {
//
//	ImGui::BeginChild("aim_child_window", ImVec2(0, 0), ImGuiWindowFlags_ChildWindow);
//
//	ImGui::Checkbox("FOV Aimbot", &settings::fov_aim);
//
//	ImGui::Text("FOV");
//
//	ImGui::SliderFloat("", &settings::fov, 1.f, 2000.f);
//
//	ImGui::EndChild();
//}

static void render::overlay() {

	if (world::is_active == false) { // Skip rendering overlay if inactive world
		return;
	}

	ImGui::SetNextWindowSize(ImVec2( render_backend::g_window_width, render_backend::g_window_height ), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2( 0.f, 0.f ), ImGuiCond_Always);
	
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);

	/**
	 * Features
	 */
	static const auto center = render_backend::get_window_center();
	render::circle(ImVec2(center.x, center.y), 75.f, ImColor(255, 255, 255, 90)); // Hardcoded 75f FOV

	/**
	 * Crosshair
	 */
	render::line(ImVec2(center.x, center.y - 10.f), ImVec2(center.x, center.y + 10.f), ImColor(255, 0, 0));
	render::line(ImVec2(center.x - 10.f, center.y), ImVec2(center.x + 10.f, center.y), ImColor(255, 0, 0));

	for(auto& player : world::players)
	{
		if (player.get_address() == 0 || player.get_address() == world::local_player.get_address()) {
			continue;
		}

		const auto root3 = player.get_root_position();
		const auto root2 = world::main_camera.world_to_screen(root3);

		if (root2 == vector2::zero) { // Skip vector2.zero
			continue;
		}

		/**
		 * Nickname
		 */
		static auto color_nickname = ImColor(212, 255, 0);
		render::text(ImVec2(root2.x, root2.y), color_nickname, player.m_name);

		/**
		 * Bones
		 */
		for (auto index = 0; index < player.m_playerbody.bone_link_indices.size(); index += 2) {

			const auto index1 = player.m_playerbody.bone_link_indices[index];
			const auto index2 = player.m_playerbody.bone_link_indices[index + 1];

			if (player.m_playerbody.m_positions.empty()) { // Skip garbage object
				continue;
			}

			const auto f3 = player.m_playerbody.m_positions[index1];
			const auto f2 = world::main_camera.world_to_screen(f3);

			const auto t3 = player.m_playerbody.m_positions[index2];
			const auto t2 = world::main_camera.world_to_screen(t3);

			if (f2 == vector2::zero || t2 == vector2::zero) { // Skip vector2.zero
				continue;
			}

			auto const color = ImColor(0, 255, 0, 255);
			
			render::line( ImVec2(f2.x, f2.y), ImVec2(t2.x, t2.y), color);
		}
	}
	
	ImGui::End();
}

static void render::text(const ImVec2& pos, const ImColor& color, const string& text) {
	ImGui::GetWindowDrawList()->AddText(pos, color, text.c_str());
}

static void render::text_stroke(const ImVec2& pos, const ImColor& color, const string& text) {
	auto draw_list = ImGui::GetWindowDrawList();
	
	draw_list->AddText( ImVec2(pos.x + 1.f, pos.y + 1.f), ImColor(0,0,0,255), text.c_str() );
	draw_list->AddText( ImVec2(pos.x + 1.f, pos.y - 1.f), ImColor(0,0,0,255), text.c_str() );
	draw_list->AddText( ImVec2(pos.x - 1.f, pos.y - 1.f), ImColor(0,0,0,255), text.c_str() );
	draw_list->AddText( ImVec2(pos.x - 1.f, pos.y + 1.f), ImColor(0,0,0,255), text.c_str() );
	
	draw_list->AddText( pos, color, text.c_str() );
}

static void render::line(const ImVec2& from, const ImVec2& to, const ImColor& color) {
	ImGui::GetWindowDrawList()->AddLine(from, to, color);
}

static void render::line_stroke(const ImVec2 from, const ImVec2 to, const ImColor color) {
	ImGui::GetWindowDrawList()->AddLine(from, to, ImColor(0,0,0,255), 1.5f);
	ImGui::GetWindowDrawList()->AddLine(from, to, color);
}

static void render::rect(const ImVec2 pos, const ImVec2 length, const ImColor color) {
	ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + length.x, pos.y + length.y), color, 0, ImDrawFlags_None);
}

void render::circle(const ImVec2& pos, const float& radius, const ImColor& color) {
	ImGui::GetWindowDrawList()->AddCircle(pos, radius, color);
}

void render::frame() {

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_HOME) & 0x01) { // Toggle menu display (xor window transparency flag)
		
		SetWindowLongPtrA(render_backend::g_window_handle, GWL_EXSTYLE, GetWindowLongA(render_backend::g_window_handle, GWL_EXSTYLE) ^ WS_EX_TRANSPARENT);
		SetForegroundWindow(render_backend::g_window_handle);
		is_menu_rendered = !is_menu_rendered;
	}

	if(is_menu_rendered) { // Render menu
		menu_window_main();
	}

	overlay();

	ImGui::Render();
	render_backend::g_d3d11_device_context->OMSetRenderTargets(1, &render_backend::g_d3d11_render_target, nullptr);
	render_backend::g_d3d11_device_context->ClearRenderTargetView(render_backend::g_d3d11_render_target, clear_color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	render_backend::g_swapchain->Present(0, 0);
}