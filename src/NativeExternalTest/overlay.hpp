#pragma once
#include <Windows.h>

#include "graphics_handler.hpp"
#include "memory_handler.hpp"

#ifndef OVERLAY_HPP
#define OVERLAY_HPP

struct visual_settings
{
	// *TEMP*

	// Contains flags for visuals

	static bool name;

	static bool health;

	static bool snapline;

	static bool box;

	static bool bones;

	static bool loot;

};

struct overlay
{
private:

	static HWND window_handle;

	static IDXGISwapChain* swapchain;

	static ID3D11Device* d3d11_device;

	static ID3D11DeviceContext* d3d11_device_context;
	
	static ID2D1DeviceContext* d2d1_device_context;

	// TODO

	// brushes

	// fonts

	// primitive drawing (lines / rectangles / circle / text )

	// IMGUI support maybe ?
	
public:

	static bool is_rendering;

	static float render_distance;
	
	static auto init() -> BOOL;

	static auto terminate() -> BOOL;

	static auto render_loop() -> void;
};

#endif