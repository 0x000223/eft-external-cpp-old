#pragma once
#include <cstdint>

#include "graphics_handler.hpp"
#include "menu.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#ifndef RENDER_HPP
#define RENDER_HPP

struct render
{
private:

	static float clear_color[4];
	
	static HWND window_handle;

	static int window_height, window_width;
	
	static IDXGISwapChain* swapchain;

	static ID3D11Device* d3d11_device;
	
	static ID3D11DeviceContext* d3d11_device_context;

	static ID3D11RenderTargetView* d3d11_render_target;

	static ID2D1DeviceContext* d2d1_device_context;

	static ID2D1RenderTarget* d2d1_render_target;

	static ImFont* font_cascadia;

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static auto overlay_window() -> void;
	
	static auto draw_text(ImVec2 pos, ImColor color, std::string text) -> void;

	static auto draw_line(ImVec2 from, ImVec2 to, ImColor color) -> void;

	static auto draw_rect(ImVec2 pos, ImVec2 length, ImColor color) -> void;

	static auto draw_filled_rect(ImVec2 pos, ImVec2 length, ImColor color) -> void;

	static auto draw_edged_rect(ImVec2 pos, ImVec2 length, ImColor color, float percent = 0.4f, float thickness = 1.f) -> void;

public:
	
	static auto init() -> BOOL;

	static auto terminate() -> BOOL;

	static auto render_frame() -> void;

	struct flags
	{
		static float draw_distance;
		
		static bool name;

		static bool health;
		
		static bool edged_box;

		static bool snapline;
	};
};

#endif