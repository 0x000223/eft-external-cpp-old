#include "render.hpp"

float					render::clear_color[4]			= { 0.f, 0.f, 0.f, 0.f };
int						render::window_height			= 0;
int						render::window_width			= 0;

HWND					render::window_handle			= nullptr;

IDXGISwapChain*			render::swapchain				= nullptr;
ID3D11Device*			render::d3d11_device			= nullptr;
ID3D11DeviceContext*	render::d3d11_device_context	= nullptr;
ID3D11RenderTargetView* render::d3d11_render_target		= nullptr;
ID2D1DeviceContext*		render::d2d1_device_context		= nullptr;
ID2D1RenderTarget*		render::d2d1_render_target		= nullptr;

ImFont*					render::font_cascadia			= nullptr;

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
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGui_ImplWin32_Init(window_handle);
	ImGui_ImplDX11_Init(d3d11_device, d3d11_device_context);

	ImGuiIO& io = ImGui::GetIO();
	
	font_cascadia = io.Fonts->AddFontFromFileTTF(R"(..\..\resources\CascadiaCode-Regular.ttf)", 13.f);
	
	menu::set_menu_style();
	
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
		menu::main_menu_window();
	}

	// Check if in raid
	overlay_window();
	
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

	{
		// Check draw distance

		// Player iteration
		
	}
	
	ImGui::End();
}

auto render::draw_text(const ImVec2 pos, const ImColor color, std::string text) -> void
{
	ImGui::PushFont(font_cascadia);
	
	ImGui::GetWindowDrawList()->AddText(pos, color, text.data(), text.data() + text.length());

	ImGui::PopFont();
}

auto render::draw_line(const ImVec2 from, const ImVec2 to, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddLine(from, to, color);
}

auto render::draw_rect(const ImVec2 pos, const ImVec2 length, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + length.x, pos.y + length.y), color, 0, ImDrawFlags_None);
}

auto render::draw_filled_rect(const ImVec2 pos, const ImVec2 length, const ImColor color) -> void
{
	ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2( pos.x + length.x, pos.y + length.y ), color);
}

auto render::draw_edged_rect(const ImVec2 pos, const ImVec2 length, const ImColor color, const float percent, const float thickness) -> void
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