
add_subdirectory (imgui)

add_subdirectory (unity_types)

add_subdirectory (scripting_types)

target_sources (client
	PUBLIC
		main.cpp
		memory.cpp
		utility.cpp
		render.cpp
		render_backend.cpp
		world.cpp)