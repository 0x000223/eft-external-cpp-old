#include "render.hpp"
#include "menu.hpp"

float					render::clear_color[4]			= { 0.f, 0.f, 0.f, 0.f };
int						render::window_height			= 0;
int						render::window_width			= 0;

ImFont*					render::font_mbender			= nullptr;
ImFont*					render::font_mbender_bold		= nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

auto render::init() -> BOOL
{
	window_handle = graphics_handler::create_window(L"Microsoft Edge");
	
	if(!window_handle)
	{
		return FALSE;
	}
	
	if(!graphics_handler::create_d3d11_device(window_handle, swapchain, d3d11_device, d3d11_device_context))
	{
		return FALSE;
	}

	if(!graphics_handler::create_d3d11_render_target(swapchain, d3d11_device, d3d11_render_target))
	{
		graphics_handler::release_dxgi_swapchain(swapchain);
		graphics_handler::release_d3d11_device(d3d11_device);

		return FALSE;
	}

	SetWindowLongPtrA(window_handle, GWLP_WNDPROC, reinterpret_cast<int64_t>(WndProc));

	ShowWindow(window_handle, SW_SHOW);
	UpdateWindow(window_handle);

	graphics_handler::get_window_size(window_handle, window_height, window_width);

	MoveWindow(window_handle, 0, 0, window_width, window_height, FALSE);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGui_ImplWin32_Init(window_handle);
	ImGui_ImplDX11_Init(d3d11_device, d3d11_device_context);

	ImGuiIO& io = ImGui::GetIO();
	
	font_mbender = io.Fonts->AddFontFromFileTTF(R"(..\..\resources\MBender.otf)", 14.f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	font_mbender_bold = io.Fonts->AddFontFromFileTTF(R"(..\..\resources\MBender-Bold.otf)", 14.f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	
	menu::menu_style_default();
	
	return TRUE;
}

auto render::terminate() -> BOOL
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	
	graphics_handler::release_d3d11_render_target(d3d11_render_target);
	graphics_handler::release_d3d11_device(d3d11_device);
	graphics_handler::release_dxgi_swapchain(swapchain);

	DestroyWindow(window_handle);
	
	return TRUE;
}

auto render::render_frame() -> void
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if(GetAsyncKeyState(VK_HOME) & 0x01) // Toggle menu display (xor window transparency flag)
	{
		SetWindowLongPtrA(window_handle, GWL_EXSTYLE, GetWindowLongA(window_handle, GWL_EXSTYLE) ^ WS_EX_TRANSPARENT);

		SetForegroundWindow(window_handle);
		
		menu::show_menu = !menu::show_menu;
	}

	if(menu::show_menu)
	{
		menu::main_window();
	}

	if(process_state::is_in_raid)
	{
		overlay_window();
	}
	
	ImGui::Render();

	d3d11_device_context->OMSetRenderTargets(1, &d3d11_render_target, nullptr);
	d3d11_device_context->ClearRenderTargetView(d3d11_render_target, clear_color);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	swapchain->Present(0, 0);
}

LRESULT render::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	switch(msg)
	{
	case WM_SIZE:

		if(d3d11_device != nullptr && wParam != SIZE_MINIMIZED)
		{
			graphics_handler::release_d3d11_render_target(d3d11_render_target);

			swapchain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_B8G8R8A8_UNORM, 0);

			graphics_handler::create_d3d11_render_target(swapchain, d3d11_device, d3d11_render_target);
		}
		
		return true;
		
	case WM_SYSCOMMAND:

		if((wParam & 0xFFF0) == SC_KEYMENU)
		{
			return 0;
		}
		
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

auto render::overlay_window() -> void
{
	ImGui::SetNextWindowSize(ImVec2( window_width, window_height ), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2( 0.f, 0.f ), ImGuiCond_Always);
	
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
	
	for(auto& player : raid_instance::players)
	{
		try
		{
			if(!player || !raid_instance::local_player || player == raid_instance::local_player)
			{
				continue;
			}

			auto head3 = player.get_head_position();
			auto head2 = camera::world_to_screen(head3);

			auto root3 = player.get_root_position();
			auto root2 = camera::world_to_screen(root3);
			
			auto local_root3 = raid_instance::local_player->get_root_position();
			
			auto distance = vector3::distance(local_root3, root3);

			auto player_height = root2.y - head2.y;
			auto player_width  = player_height * 0.35f;

			auto player_health = player.get_health();

			if(distance > settings::player_draw_distance)
			{
				continue;
			}
			
			if(!head2)
			{
				continue;
			}
			
			if(settings::player_name)
			{
				auto const pos = ImVec2(head2.x - 30.f, head2.y - 35.f);
				auto const color = ImColor(255, 255, 205, 255);
				
				draw_text_stroke( pos, color, player.name);
			}

			if(settings::player_health)
			{
				auto const pos = ImVec2( head2.x - 10.f, head2.y - 20.f );
				auto const color = ImColor(255, 0, 0, 255);
				
				draw_text_stroke( pos, color, std::to_string( static_cast<int>(player_health) ));
			}
			
			if(settings::player_distance)
			{
				auto const pos = ImVec2(root2.x - 5.f, root2.y + 10.f);
				auto const color = ImColor(255, 255, 255, 255);
				
				draw_text_stroke( pos, color, std::to_string( static_cast<int>(distance) ));
			}

			if(settings::player_faction)
			{
				auto const pos = ImVec2(head2.x - 20.f, head2.y - 50.f);
				auto const color = ImColor(255, 255, 255, 255);
				
				draw_text_stroke(pos, color, player.faction);
			}

			if(settings::player_bones)
			{
				for(auto& [from, to] : player.body->bone_links)
				{
					auto from3 = from.get_position();
					auto to3 = to.get_position();

					auto const from2 = camera::world_to_screen(from3);
					auto const to2 = camera::world_to_screen(to3);

					auto const color = ImColor(0, 255, 0, 255);
					
					draw_line( ImVec2(from2.x, from2.y), ImVec2(to2.x, to2.y), color);
				}
			}
			
			if(settings::player_snapline)
			{
				auto const color = ImColor(255, 0, 0, 255);
				
				draw_line_stroke( ImVec2(1920.f / 2.f, 0.f), ImVec2(head2.x, head2.y), color);
				ImGui::GetWindowDrawList()->AddCircleFilled( ImVec2(head2.x, head2.y), 2.f, ImColor(178,40,40,255));
			}

			if(settings::player_box)
			{
				auto const pos = ImVec2(head2.x - 15.f, head2.y - 10.f);
				auto const color = ImColor(0,0,205,255);
				
				draw_rect_stroke( pos, ImVec2(head2.x + player_width, head2.y + player_height), color);
			}

			if(settings::fov_aim)
			{
				auto const color = ImColor(0,0,255,255);
				
				ImGui::GetWindowDrawList()->AddCircle( ImVec2(1920.f / 2.f, 1080.f / 2.f), settings::fov, color);
			}
		}
		catch (...) { }
	}
	
	ImGui::End();
}

auto render::draw_text(const ImVec2 pos, const ImColor color, std::string text) -> void
{
	ImGui::GetWindowDrawList()->AddText(pos, color, text.c_str());
}

auto render::draw_text_stroke(const ImVec2 pos, const ImColor color, const std::string text) -> void
{
	auto draw_list = ImGui::GetWindowDrawList();
	
	draw_list->AddText( ImVec2(pos.x + 1.f, pos.y + 1.f), ImColor(0,0,0,255), text.c_str() );
	draw_list->AddText( ImVec2(pos.x + 1.f, pos.y - 1.f), ImColor(0,0,0,255), text.c_str() );
	draw_list->AddText( ImVec2(pos.x - 1.f, pos.y - 1.f), ImColor(0,0,0,255), text.c_str() );
	draw_list->AddText( ImVec2(pos.x - 1.f, pos.y + 1.f), ImColor(0,0,0,255), text.c_str() );
	
	draw_list->AddText( pos, color, text.c_str() );
}

auto render::draw_line(const ImVec2 from, const ImVec2 to, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddLine(from, to, color);
}

auto render::draw_line_stroke(const ImVec2 from, const ImVec2 to, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddLine(from, to, ImColor(0,0,0,255), 1.5f);
	ImGui::GetWindowDrawList()->AddLine(from, to, color);
}

auto render::draw_rect(const ImVec2 pos, const ImVec2 length, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + length.x, pos.y + length.y), color, 0, ImDrawFlags_None);
}

auto render::draw_rect_stroke(const ImVec2 pos, const ImVec2 length, const ImColor color, const ImColor outline_color) -> void
{
	ImGui::GetWindowDrawList()->AddRect(pos, length, outline_color, 0.f, 0, 1.5f);

	ImGui::GetWindowDrawList()->AddRect(pos, length, color);
}

auto render::draw_rect_filled(const ImVec2 pos, const ImVec2 length, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2( pos.x + length.x, pos.y + length.y ), color);
}

auto render::draw_edged_rect(const ImVec2 pos, const ImVec2 length, const ImColor color, const float percent, const float thickness, const bool outline) -> void
{
	auto* draw_list = ImGui::GetWindowDrawList();

	ImVec2 max = { pos.x + length.x, pos.y + length.y };
	
	draw_list->AddLine(pos, ImVec2( pos.x + length.x * percent, pos.y ), color, thickness);
	draw_list->AddLine(ImVec2( max.x, pos.y ), ImVec2( max.x - length.x * percent, pos.y), color, thickness);

	draw_list->AddLine(ImVec2( pos.x, max.y ), ImVec2( pos.x + length.x * percent, max.y ), color, thickness);
	draw_list->AddLine(max, ImVec2( max.x - length.x * percent, max.y ), color, thickness);

	draw_list->AddLine(pos, ImVec2( pos.x, pos.y + length.y * percent ), color, thickness);
	draw_list->AddLine(ImVec2( pos.x, max.y), ImVec2( pos.x, max.y - length.y * percent ), color, thickness);

	draw_list->AddLine(ImVec2( max.x, pos.y ), ImVec2( max.x, pos.y + length.y * percent ), color, thickness);
	draw_list->AddLine(max, ImVec2( max.x, max.y - length.y * percent ), color, thickness);
}