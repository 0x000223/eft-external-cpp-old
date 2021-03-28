#include "menu.hpp"




float menu::window_width	= 450;
float menu::window_height	= 500;

HWND menu::window_handle = nullptr;

WNDCLASSEX menu::wc = { 0 };

IDXGISwapChain*		menu::swapchain			= nullptr;
ID3D11Device*		menu::d3d11_device		= nullptr;
ID3D11DeviceContext*	menu::d3d11_device_context	= nullptr;
ID3D11RenderTargetView* menu::d3d11_render_target	= nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL menu::init()
{
	const wchar_t* class_name = L"ExternalTest";
	const wchar_t* window_name = L"ExternalTestMenu";

	int posX = 0;
	int posY = 0;

	auto window_style = WS_OVERLAPPED;
	auto ex_window_style = NULL;
	
	graphics_handler::create_native_window(window_handle, wc, WndProc, 
		class_name, window_name, posX, posY, window_width, window_height, ex_window_style, window_style);

	if(!window_handle)
	{
		return FALSE;
	}

	if(!graphics_handler::create_d3d11_device(window_handle, swapchain, d3d11_device, d3d11_device_context))
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return FALSE;
	}

	if(!graphics_handler::create_d3d11_render_target(swapchain, d3d11_device, d3d11_render_target))
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		
		graphics_handler::release_dxgi_swapchain(swapchain);
		graphics_handler::release_d3d11_device(d3d11_device);

		return FALSE;
	}

	ShowWindow(window_handle, SW_SHOW);
	UpdateWindow(window_handle);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); // TODO

	ImGui_ImplWin32_Init(window_handle);
	ImGui_ImplDX11_Init(d3d11_device, d3d11_device_context);
	
	return TRUE;
}

BOOL menu::terminate()
{
	// Resource cleanup

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	
	graphics_handler::release_d3d11_render_target(d3d11_render_target);
	graphics_handler::release_d3d11_device(d3d11_device);
	graphics_handler::release_dxgi_swapchain(swapchain);

	DestroyWindow(window_handle);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	
	return TRUE;
}

void menu::render_frame()
{
	// TEMP - static window flags
	
	static float clear_color[4] = { 0.f, 0.f, 0.f, 0.f };

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(window_width - 16.f, window_height - 39.f)); // Magic
	
	window_main();

	ImGui::Render();

	d3d11_device_context->OMSetRenderTargets(1, &d3d11_render_target, nullptr);
	d3d11_device_context->ClearRenderTargetView(d3d11_render_target, clear_color);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swapchain->Present(1, 0);
}

LRESULT menu::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

			swapchain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);

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

auto menu::window_main() -> void
{
	ImGui::Begin("Sample window!", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration);

	if(ImGui::BeginTabBar("tab_bar_01"))
	{
		if(ImGui::BeginTabItem("Features"))
		{
			ImGui::BeginChild("features_child");

				{
					// Visuals - (health / box / snaplines / bones / loot / draw distance)

					// Functionality - (recoil / stamina / aim)

					// Color settings
				}

			ImGui::EndChild();
			
			ImGui::EndTabItem();
		}

		if(ImGui::BeginTabItem("Instance"))
		{
			ImGui::BeginChild("instance_child");

				{
					// Display data about current raid

					
				}
				
			ImGui::EndChild();
			
			ImGui::EndTabItem();
		}
		
		if(ImGui::BeginTabItem("State"))
		{
			ImGui::BeginChild("state_child");

				{
					// Handle state
				
					ImGui::Text("Object Manager: 0x%llX", managers::game_object_manager);

					ImGui::Text("Render Manager: 0x%llX", managers::render_manager);
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
