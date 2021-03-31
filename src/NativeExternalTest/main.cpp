#include <Windows.h>

#include "memory_handler.hpp"
#include "managers.hpp"
#include "process_state.hpp"
#include "render.hpp"

#pragma warning (disable : 28251)

auto WinMain(HINSTANCE, HINSTANCE, char*, int) -> int
{
	memory_handler::init();
	
	process_state::init();

	render::init();

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

		render::render_frame();
		
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
		
		scripts::run_scripts();
	}

	render::terminate();
	
	memory_handler::terminate();

	return 0;
}