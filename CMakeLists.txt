cmake_minimum_required(VERSION 3.16.3)
project(triangles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE)

add_executable(triangles
		src/main.cpp
		src/load_shaders.cpp
#		src/window.cpp
)

add_subdirectory(external)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

target_include_directories(triangles PUBLIC inc/)
target_link_libraries(triangles PUBLIC
  ${ALL_LIBS}
)