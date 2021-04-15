#include <Windows.h>
#include <thread>

#include "memory_handler.hpp"
#include "managers.hpp"
#include "process_state.hpp"
#include "render.hpp"

#pragma warning (disable : 28251)

auto WinMain(HINSTANCE, HINSTANCE, char*, int) -> int
{
	memory_handler::init();
	
	process_state::init();

	managers::init();
	
	render::init();

	std::thread thread_state_monitor { process_state::process_state_monitor };
	thread_state_monitor.detach();
	
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

		if(process_state::is_in_raid)
		{
			scripts::run_scripts();
		}
	}

	render::terminate();

	managers::release();
	
	process_state::release();
	
	memory_handler::terminate();

	return 0;
}