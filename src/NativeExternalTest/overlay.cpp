#include "overlay.hpp"

bool overlay::is_rendering = false;

float overlay::render_distance = 0.f;

HWND overlay::window_handle = nullptr;

IDXGISwapChain* overlay::swapchain = nullptr;

ID3D11Device* overlay::d3d11_device = nullptr;

ID3D11DeviceContext* overlay::d3d11_device_context = nullptr;

ID2D1DeviceContext* overlay::d2d1_device_context = nullptr;

auto overlay::init() -> BOOL
{
	window_handle = imported::create_overlay(L"Microsoft Edge");

	if(!window_handle)
	{
		return FALSE;
	}

	if(!graphics_handler::create_d3d11_device(window_handle, swapchain, d3d11_device, d3d11_device_context))
	{
		DestroyWindow(window_handle);
		return FALSE;
	}
	
	if(!graphics_handler::create_d2d1_device_context(swapchain, d3d11_device, d2d1_device_context))
	{
		DestroyWindow(window_handle);
		graphics_handler::release_dxgi_swapchain(swapchain);
		graphics_handler::release_d3d11_device(d3d11_device);
		graphics_handler::release_d3d11_device_context(d3d11_device_context);
		return FALSE;
	}

	return TRUE;
}

auto overlay::terminate() -> BOOL
{
	DestroyWindow(window_handle);

	graphics_handler::release_dxgi_swapchain(swapchain);
	graphics_handler::release_d3d11_device(d3d11_device);
	graphics_handler::release_d3d11_device_context(d3d11_device_context);
	graphics_handler::release_d2d1_device_context(d2d1_device_context);

	return TRUE;
}

auto overlay::render_loop() -> void
{

	// Maybe handle rendering via IMGUI
	
	while(is_rendering)
	{

		// Render frame
		
	}
	
}
