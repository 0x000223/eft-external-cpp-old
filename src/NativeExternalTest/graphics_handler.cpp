#include "graphics_handler.hpp"

#pragma warning (disable : 6387)
#pragma warning (disable : 4996)

inline auto graphics_handler::create_window(const wchar_t* title_name = L"Default IME") -> HWND
{
	return imported::create_overlay(title_name);
}

auto graphics_handler::create_native_window(HWND& window_handle, WNDCLASSEX& window_class,WNDPROC wndproc, const wchar_t* class_name, const wchar_t* window_name, 
	int posX, int posY, int width, int height, DWORD extended_window_style, DWORD window_style) -> BOOL
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

	window_handle = CreateWindowExW
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

auto graphics_handler::get_window_size(HWND handle, int& height, int& width) -> BOOL
{
	RECT rect;

	auto result = GetWindowRect(handle, &rect);
	
	height	= rect.bottom - rect.top;
	width	= rect.right  - rect.left;

	return result;
}

auto graphics_handler::create_d3d11_device(const HWND window_handle, IDXGISwapChain*& swapchain, ID3D11Device*& device, ID3D11DeviceContext*& device_context) -> BOOL
{
	if(!window_handle)
	{
		return FALSE;
	}
	
	DXGI_MODE_DESC md { 0 };

	md.Height					= 0;
	md.Width					= 0;
	md.Format					= DXGI_FORMAT_B8G8R8A8_UNORM;
	md.RefreshRate					= DXGI_RATIONAL { 60, 1 };
	
	DXGI_SWAP_CHAIN_DESC cd { 0 };

	cd.BufferCount					= 1;
	cd.BufferDesc					= md;
	cd.Windowed					= TRUE;
	cd.OutputWindow					= window_handle;
	cd.SampleDesc					= DXGI_SAMPLE_DESC { 1, 0 };
	cd.BufferUsage					= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	cd.SwapEffect					= DXGI_SWAP_EFFECT_DISCARD;
	cd.Flags					= NULL;

	D3D_FEATURE_LEVEL feature_level_array[] = 
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	auto result = D3D11CreateDeviceAndSwapChain
	(
		nullptr,				// DXGI adapter
		D3D_DRIVER_TYPE_HARDWARE,		// Driver type
		nullptr,				// Software
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,	// Flags
		feature_level_array,			// Feature levels
		_countof(feature_level_array),		// Feature levels count
		D3D11_SDK_VERSION,			// SDK version
		&cd,					// Swapchain descriptor
		&swapchain,				// Swapchain pointer
		&device,				// D3D11 device pointer
		nullptr,				// Feature levels supported
		&device_context				// D3D11 device context pointer
	);

	if(FAILED(result))
	{
		return FALSE;
	}

	return TRUE;
}

auto graphics_handler::create_d3d11_render_target(IDXGISwapChain* swapchain, ID3D11Device* device, ID3D11RenderTargetView*& render_target) -> BOOL
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

auto graphics_handler::create_d2d1_device_context(IDXGISwapChain* swapchain, ID3D11Device* device, ID2D1DeviceContext*& device_context) -> BOOL
{
	// How to render using a Direct2D device context
	// https://docs.microsoft.com/en-us/windows/win32/direct2d/devices-and-device-contexts#how-to-create-a-direct2d-device-context-for-rendering
	
	if(!swapchain)
	{
		return FALSE;
	}

	IDXGIDevice* dxgi_device;
	if(device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgi_device)) != S_OK)
	{
		return FALSE;
	}
	
	ID2D1Factory1* d2d1_factory;
	if(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d1_factory) != S_OK)
	{
		return FALSE;
	}

	ID2D1Device* d2d1_device;
	if(d2d1_factory->CreateDevice(dxgi_device, &d2d1_device) != S_OK)
	{
		return FALSE;
	}
	
	if(d2d1_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &device_context) != S_OK)
	{
		return FALSE;
	}

	float dpiX, dpiY;
	d2d1_factory->GetDesktopDpi(&dpiX, &dpiY);
	
	D2D1_BITMAP_PROPERTIES1 bitmap_prop = D2D1::BitmapProperties1
	(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpiX,
		dpiY
	);

	IDXGISurface* dxgi_surface;
	if(swapchain->GetBuffer(0, IID_PPV_ARGS(&dxgi_surface)) != S_OK)
	{
		return FALSE;
	}

	ID2D1Bitmap1* target_bitmap;
	if(device_context->CreateBitmapFromDxgiSurface(dxgi_surface, &bitmap_prop, &target_bitmap) != S_OK)
	{
		return FALSE;
	}

	device_context->SetTarget(target_bitmap);

	return TRUE;
}

auto graphics_handler::release_dxgi_swapchain(IDXGISwapChain* swapchain) -> void
{
	if(swapchain)
	{
		swapchain->Release();
		swapchain = nullptr;
	}
}

auto graphics_handler::release_d3d11_device(ID3D11Device* device) -> void
{
	 if(device)
	 {
	 	device->Release();
	 	device = nullptr;
	 }
}

auto graphics_handler::release_d3d11_device_context(ID3D11DeviceContext* device_context) -> void
{
	if(device_context)
	{
		device_context->Release();
		device_context = nullptr;
	}
}

auto graphics_handler::release_d3d11_render_target(ID3D11RenderTargetView* render_target) -> void
{
	if(render_target)
	{
		render_target->Release();
		render_target = nullptr;
	}
}

auto graphics_handler::release_d2d1_device_context(ID2D1DeviceContext* device_context) -> void
{
	if(device_context)
	{
		device_context->Release();
		device_context = nullptr;
	}
}

auto graphics_handler::create_solid_brushes() -> void
{
	solid_brushes =
		{
			{ D2D1::ColorF::Black, nullptr },
			{ D2D1::ColorF::White, nullptr },
			{ D2D1::ColorF::Red,   nullptr },
			{ D2D1::ColorF::Green, nullptr },
			{ D2D1::ColorF::Blue,  nullptr }
		};

	for(auto& brush : solid_brushes)
	{
		//this->d2d1_device_context->CreateSolidColorBrush(D2D1::ColorF(brush.first), &brush.second);
	}
}

auto graphics_handler::release_solid_brushes() -> void
{
	this->solid_brushes.clear();
}
