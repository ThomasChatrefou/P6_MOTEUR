
cmake_minimum_required(VERSION 3.23)

project(MyEngine)
include(glew.cmake)
add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)

add_executable(MyEngine main.cpp 
	Includes.hpp
	shaders/LoadShader.hpp
	GetAppPath.h GetAppPath.cpp
	Geometry.h Geometry.cpp
	MyApp.h MyApp.cpp
	Camera.h Camera.cpp
	Triangle.h Triangle.cpp
)
target_include_directories(MyEngine PRIVATE 
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)
target_link_libraries(MyEngine PRIVATE SDL2main SDL2-static opengl32 glew)

add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:MyEngine>/shaders)

add_dependencies(MyEngine copy_shaders)

set_property(TARGET MyEngine PROPERTY CXX_STANDARD 17)