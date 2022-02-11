
add_subdirectory (imgui)

# add_subdirectory (scripting_types)

# add_subdirectory (unity_types)

target_sources (client
	PUBLIC
		main.cpp
		render.hpp
		render.cpp
		graphics_handler.hpp
		graphics_handler.cpp)