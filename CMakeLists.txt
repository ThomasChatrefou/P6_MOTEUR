
cmake_minimum_required(VERSION 3.23)

project(MyEngine)
include(glew.cmake)
add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)
set(IMGUI_INCLUDE_DIR ${IMGUI_DIR} ${IMGUI_DIR}/backends)

add_executable(MyEngine main.cpp 
	Includes.hpp
	shaders/LoadShader.hpp
	GetAppPath.h GetAppPath.cpp
	Geometry.h Geometry.cpp
	MyApp.h MyApp.cpp
	Camera.h Camera.cpp
	Triangle.h Triangle.cpp
	Cube.h Cube.cpp
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


set(IMGUI_SRCS

${IMGUI_DIR}/imgui.cpp
${IMGUI_DIR}/imgui_draw.cpp
${IMGUI_DIR}/imgui_tables.cpp
${IMGUI_DIR}/imgui_widgets.cpp
${IMGUI_DIR}/backends/imgui_impl_sdl.cpp
)

# swap implementation between OGL3 and OGL2
if(${IMGUI_USE_OGL3})
  # supposes that GLEW is available
  add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
  set(IMGUI_SRCS ${IMGUI_SRCS} ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
else()
  set(IMGUI_SRCS ${IMGUI_SRCS} ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp)
endif()

add_library(imgui STATIC ${IMGUI_SRCS})
target_include_directories(imgui PRIVATE 
  ${IMGUI_DIR}
  ${SDL_INCLUDE_DIR}
)

if(${IMGUI_USE_OGL3})
target_link_libraries(imgui glew)
endif()