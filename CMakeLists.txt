# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)

project ("eft-external-cpp")

add_executable (client)

add_subdirectory (src)

target_include_directories (client
	PUBLIC
		include)

target_compile_features (client
	PUBLIC
		cxx_std_20)