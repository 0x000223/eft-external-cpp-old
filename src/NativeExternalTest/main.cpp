#include <Windows.h>

#include "memory_handler.hpp"
#include "managers.hpp"
#include "graphics_handler.hpp"
#include "process_state.hpp"
#include "menu.hpp"

#pragma warning (disable : 28251)

auto WinMain(HINSTANCE, HINSTANCE, char*, int) -> int
{
	memory_handler::init();
	
	process_state::init();

	menu::init();

	managers::init();
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		menu::render_frame();
		
		if(!process_state::is_heartbeat())
		{
			// Handle process not running

			if(process_state::init())
			{
				managers::init();
			}
			
			continue;
		}

		if(!process_state::is_in_raid())
		{
			// Handle process not in raid

			continue;
		}
		
		// Run scripts

	}

	menu::terminate();
	
	memory_handler::terminate();

	return 0;
}