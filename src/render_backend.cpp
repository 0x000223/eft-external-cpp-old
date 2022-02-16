#include "render_backend.hpp"

#include <cstdint>
#include "imgui/imgui.h"

extern HWND render_backend::g_window_handle = nullptr;
extern ID3D11Device* render_backend::g_d3d11_device = nullptr;
extern ID3D11RenderTargetView* render_backend::g_d3d11_render_target = nullptr;
extern ID3D11DeviceContext* render_backend::g_d3d11_device_context = nullptr;
extern IDXGISwapChain* render_backend::g_swapchain = nullptr;

extern int render_backend::g_window_height = 0;
extern int render_backend::g_window_width = 0;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL render_backend::create_window(HWND& window_handle, WNDCLASSEX& window_class,WNDPROC wndproc, const char* class_name, const char* window_name, 
	int posX, int posY, int width, int height, DWORD extended_window_style, DWORD window_style)
{
	ZeroMemory(&window_class, sizeof(window_class));

	window_class = 
	{
		sizeof(WNDCLASSEX),
		NULL,
		wndproc,
		0,
		0,
		GetModuleHandle(nullptr),
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		class_name,
		nullptr
	};

	RegisterClassEx(&window_class);

	window_handle = CreateWindowEx
	(
		extended_window_style,
		class_name,
		window_name,
		window_style,
		posX,
		posY,
		width,
		height,
		nullptr,
		nullptr,
		window_class.hInstance,
		nullptr
	);
	
	return window_handle != nullptr;
}

BOOL render_backend::get_window_size(HWND handle, int& height, int& width)
{
	RECT rect;

	auto result = GetWindowRect(handle, &rect);
	
	height	= rect.bottom - rect.top;
	width	= rect.right  - rect.left;

	return result;
}

BOOL render_backend::d3d11_create_device(const HWND window_handle, IDXGISwapChain*& swapchain, ID3D11Device*& device, ID3D11DeviceContext*& device_context)
{
	if(!window_handle)
	{
		return FALSE;
	}
	
	DXGI_MODE_DESC md { 0 };

	md.Height					= 0;
	md.Width					= 0;
	md.Format					= DXGI_FORMAT_B8G8R8A8_UNORM;
	md.RefreshRate				= DXGI_RATIONAL { 60, 1 };
	
	DXGI_SWAP_CHAIN_DESC cd { 0 };

	cd.BufferCount					= 1;
	cd.BufferDesc					= md;
	cd.Windowed						= TRUE;
	cd.OutputWindow					= window_handle;
	cd.SampleDesc					= DXGI_SAMPLE_DESC { 1, 0 };
	cd.BufferUsage					= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	cd.SwapEffect					= DXGI_SWAP_EFFECT_DISCARD;
	cd.Flags						= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL feature_level_array[] = 
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	auto result = D3D11CreateDeviceAndSwapChain
	(
		nullptr,							// DXGI adapter
		D3D_DRIVER_TYPE_HARDWARE,			// Driver type
		nullptr,							// Software
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,	// Flags
		feature_level_array,				// Feature levels
		_countof(feature_level_array),		// Feature levels count
		D3D11_SDK_VERSION,					// SDK version
		&cd,								// Swapchain descriptor
		&swapchain,							// Swapchain pointer
		&device,							// D3D11 device pointer
		nullptr,							// Feature levels supported
		&device_context						// D3D11 device context pointer
	);

	if(FAILED(result))
	{
		return FALSE;
	}

	return TRUE;
}

void render_backend::d3d11_release_device(ID3D11Device* device)
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}
}

BOOL render_backend::d3d11_create_render_target(IDXGISwapChain* swapchain, ID3D11Device* device, ID3D11RenderTargetView*& render_target)
{
	ID3D11Texture2D* back_buffer;

	swapchain->GetBuffer
	(
		NULL, 
		__uuidof(ID3D11Texture2D), 
		reinterpret_cast<void**>(&back_buffer)
	);
	
	auto result = device->CreateRenderTargetView(back_buffer, nullptr, &render_target);

	back_buffer->Release();

	return result == S_OK ? TRUE : FALSE;
}

void render_backend::d3d11_release_render_target(ID3D11RenderTargetView* render_target)
{
	if (render_target)
	{
		render_target->Release();
		render_target = nullptr;
	}
}

void render_backend::d3d11_release_device_context(ID3D11DeviceContext* device_context)
{
	if (device_context)
	{
		device_context->Release();
		device_context = nullptr;
	}
}

void render_backend::dxgi_release_swapchain(IDXGISwapChain* swapchain)
{
	if(swapchain)
	{
		swapchain->Release();
		swapchain = nullptr;
	}
}

LRESULT render_backend::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	switch (msg)
	{
	case WM_SIZE:

		if (g_d3d11_device != nullptr && wParam != SIZE_MINIMIZED)
		{
			d3d11_release_render_target(g_d3d11_render_target);

			g_swapchain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_B8G8R8A8_UNORM, 0);

			render_backend::d3d11_create_render_target(g_swapchain, g_d3d11_device, g_d3d11_render_target);
		}

		return true;

	case WM_SYSCOMMAND:

		if ((wParam & 0xFFF0) == SC_KEYMENU)
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

BOOL render_backend::initialize() {

	static WNDCLASSEX wndclassex;

	create_window(
		g_window_handle,
		wndclassex,
		WndProc,
		"Chrome_WidgetWin_1",
		"Core Input",
		0,
		0,
		1920,
		1080,
		WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
		WS_VISIBLE | WS_MAXIMIZE);

	if (d3d11_create_device(g_window_handle, g_swapchain, g_d3d11_device, g_d3d11_device_context) == FALSE) {
		terminate();
		return FALSE;
	}

	if (d3d11_create_render_target(g_swapchain, g_d3d11_device, g_d3d11_render_target) == FALSE) {
		terminate();
		return FALSE;
	}

	SetWindowLongPtrA(g_window_handle, GWLP_WNDPROC, reinterpret_cast<int64_t>(WndProc));

	ShowWindow(g_window_handle, SW_SHOW);
	UpdateWindow(g_window_handle);

	get_window_size(g_window_handle, g_window_height, g_window_width);

	MoveWindow(g_window_handle, 0, 0, g_window_width, g_window_height, FALSE);
}

void render_backend::terminate() {
	d3d11_release_render_target(g_d3d11_render_target);
	d3d11_release_device(g_d3d11_device);
	dxgi_release_swapchain(g_swapchain);
	DestroyWindow(g_window_handle);
}