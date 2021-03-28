#pragma once
#include <Windows.h>
#include <string>

#include "graphics_handler.hpp"
#include "memory_handler.hpp"
#include "overlay.hpp"
#include "managers.hpp"
#include "game_object.hpp"
#include "camera.hpp"
#include "unity.hpp"
#include "debug.hpp"

#include "CC_BrightnessContrastGamma.hpp"
#include "ThermalVision.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#ifndef MENU_HPP
#define MENU_HPP

// Agregate dependencies (platforms handles / rendering devices)

// Styles

// Windows

// Display settings

struct menu
{
private:

	static float window_width;

	static float window_height;
	
	static HWND window_handle;
	
	static WNDCLASSEX wc;
	
	static IDXGISwapChain* swapchain;

	static ID3D11Device* d3d11_device;
	
	static ID3D11DeviceContext* d3d11_device_context;

	static ID3D11RenderTargetView* d3d11_render_target;
	
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


	static auto window_main() -> void;
	
public:

	static BOOL init();

	static BOOL terminate();

	static void render_frame();
};

#endif