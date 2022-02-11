/**
 * @file render_backend.hpp
 * @date 11/02/2022
 * 
 * @brief 
 */

#ifndef GRAPHICS_HANDLER_HPP
#define GRAPHICS_HANDLER_HPP

#include <Windows.h>
#include <d3d11.h>
#include <d2d1.h>
#include <d2d1_1.h>

#include "utility.hpp"

class graphics_handler
{
public:
	
	graphics_handler() = default;

	static auto create_window(const wchar_t* title_name) -> HWND;
	
	static auto create_native_window(HWND& window_handle, WNDCLASSEX& window_class,WNDPROC wndproc, const wchar_t* class_name, const wchar_t* window_name, int posX, int posY, int width, int height, DWORD extended_window_style = 0, DWORD window_style = 0) -> BOOL;

	static auto get_window_size(HWND handle, int& height, int& width) -> BOOL;
	
	static auto create_d3d11_device(HWND window_handle, IDXGISwapChain*& swapchain, ID3D11Device*& device, ID3D11DeviceContext*& device_context) -> BOOL;

	static auto create_d3d11_render_target(IDXGISwapChain* swapchain, ID3D11Device* device, ID3D11RenderTargetView*& render_target) -> BOOL;

	static auto create_d2d1_device_context(IDXGISwapChain* swapchain, ID3D11Device* device, ID2D1DeviceContext*& device_context) -> BOOL;

	static auto create_d2d11_render_target(IDXGISwapChain* swapchain, ID2D1RenderTarget*& d2d1_render_target) -> BOOL;

	static auto release_dxgi_swapchain(IDXGISwapChain* swapchain) -> void;

	static auto release_d3d11_device(ID3D11Device* device) -> void;

	static auto release_d3d11_device_context(ID3D11DeviceContext* device_context) -> void;

	static auto release_d3d11_render_target(ID3D11RenderTargetView* render_target) -> void;

	static auto release_d2d1_device_context(ID2D1DeviceContext* device_context) -> void;

	static auto release_d2d11_render_target(ID2D1RenderTarget* d2d1_render_target) -> void;
};

#endif