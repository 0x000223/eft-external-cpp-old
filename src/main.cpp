#include <Windows.h>
#include <thread>
#include <future>

#include "memory.hpp"
#include "render.hpp"
#include "render_backend.hpp"
#include "feature.hpp"

#include "unity_types/game_object.hpp"

#pragma warning (disable : 28251)

int WinMain(HINSTANCE, HINSTANCE, char*, int) {

	memory::init();
	
	const auto did_init = render_backend::initialize();

	process::g_process_id = process::get_process_id("EscapeFromTarkov.exe");
	process::g_module_address = process::get_module_address(L"UnityPlayer.dll");

	g_GOM = memory::read<address_t>(process::g_module_address + O_GOM);

	// Launch async task to check if 'EscapeFromTarkov.exe' is still running
	// if not, then terminate this program
	std::future<void> task_process_state = std::async(std::launch::async, []() {
		while (true) {
			if (process::get_process_id("EscapeFromTarkov.exe") == 0) {
				exit(-1);
			}
			Sleep(1000);
		}
	});
	
	// Monitor and update world state - Camera & GameWorld
	std::future<void> task_world_state = std::async(std::launch::async, []() {
		while (true) {
			world::update_state();
			Sleep(1000);
		}
	});

	// Monitor player list task
	std::future<void> task_update_players = std::async(std::launch::async, []() {
		while (true) {
			world::update_players();
			Sleep(1000);
		}
	});
	
	std::future<void> task_update_positions = std::async(std::launch::async, []() {
		while (true) {
			if (world::is_active && !world::players.empty()) {
				for (auto& player : world::players) { // Need to filter junk objects to avoid access invalid memory
					for (auto index = 0; index < player.m_playerbody.m_transforms.size(); ++index) {
						try
						{
							player.m_playerbody.m_positions[index] = player.m_playerbody.m_transforms[index].get_position();
						}
						catch (...) {}; // TEMP Workaround
					}
				}
			}
			Sleep(50);
		}
	});

	std::future<void> task_features = std::async(std::launch::async, []() {
		while (true) {
			if (world::is_active) {
				
				/**
				 * Stamina Filler
				 */
				world::local_player.fill_stamina(300);

				/**
				 * No Recoil
				 */
				feature::no_recoil();

				/**
				 *  FOV Aimbot
				 */
				if (GetAsyncKeyState(0x46)) { // 'F' - aimbot_fov
					feature::aimbot_fov();
				}
			}
			Sleep(100);
		}
	});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(render_backend::g_window_handle);
	ImGui_ImplDX11_Init(render_backend::g_d3d11_device, render_backend::g_d3d11_device_context);

	ImGuiIO& io = ImGui::GetIO();
	auto font_mbender = io.Fonts->AddFontFromFileTTF(R"(C:\Users\Max\Desktop\MBender.otf)", 14.f, nullptr, io.Fonts->GetGlyphRangesCyrillic()); // Temp for Cyrillic testing

	render::menu_set_style_default();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while(msg.message != WM_QUIT) {

		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		
		render::frame();
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	render_backend::terminate();
	memory::terminate();

	return 0;
}