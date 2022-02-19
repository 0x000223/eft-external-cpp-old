# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)

project ("eft-external-cpp")

add_executable (client WIN32)

# client private sources
add_subdirectory (src)

target_include_directories (client
	PRIVATE
		src
	PUBLIC
		include)

target_compile_features (client
	PUBLIC
		cxx_std_20)

target_link_libraries (client
	PUBLIC
		d3d11.lib)