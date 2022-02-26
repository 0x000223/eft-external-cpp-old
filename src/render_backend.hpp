/*****************************************************************//**
 * \file   render_backend.hpp
 * \brief  
 * 
 * \author Max
 * \date   February 2022
 *********************************************************************/

#ifndef RENDER_BACKEND_HPP
#define RENDER_BACKEND_HPP

#include <Windows.h>
#include <d3d11.h>

#include "math.hpp"

namespace render_backend {
	
	/**
	 * @brief
	 */
	extern HWND	g_window_handle;

	/**
	 * @brief
	 */
	extern int g_window_height, g_window_width;

	/**
	 * @brief
	 */
	extern IDXGISwapChain* g_swapchain;

	/**
	 * @brief
	 */
	extern ID3D11Device* g_d3d11_device;

	/**
	 * @brief
	 */
	extern ID3D11DeviceContext* g_d3d11_device_context;

	/**
	 * @brief
	 */
	extern ID3D11RenderTargetView* g_d3d11_render_target;

	/**
	 * @brief
	 */
	static BOOL d3d11_create_device(const HWND window_handle, IDXGISwapChain*& swapchain, ID3D11Device*& device, ID3D11DeviceContext*& device_context);

	/**
	 * @brief
	 */
	static void d3d11_release_device(ID3D11Device* device);

	/**
	 * @brief
	 */
	static BOOL d3d11_create_render_target(IDXGISwapChain* swapchain, ID3D11Device* device, ID3D11RenderTargetView*& render_target);

	/**
	 * @brief
	 */
	static void d3d11_release_render_target(ID3D11RenderTargetView* render_target);

	/**
	 * @brief
	 */
	static void d3d11_release_device_context(ID3D11DeviceContext* device_context);

	/**
	 * @brief
	 */
	static void dxgi_release_swapchain(IDXGISwapChain* swapchain);

	/**
	 * @brief
	 */
	static BOOL create_window(HWND& window_handle, WNDCLASSEX& window_class, const char* window_name, int posX, int posY, int width, int height, DWORD extended_window_style = 0, DWORD window_style = 0);

	/**
	 * @brief
	 */
	BOOL get_window_size(HWND handle, int& height, int& width);

	/**
	 * @brief
	 */
	vector2 get_window_center();

	/**
	 * @brief
	 */
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief
	 */
	BOOL initialize();

	/**
	 * @brief
	 */
	void terminate();
}

#endif