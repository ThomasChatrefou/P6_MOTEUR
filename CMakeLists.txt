
cmake_minimum_required(VERSION 3.23)

project(MyEngine)
include(cmake/glew.cmake)
include(cmake/assimp.cmake)
add_subdirectory(dep/SDL dep/SDL)

set(IMGUI_USE_OGL3 true)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)
set(IMGUI_INCLUDE_DIR ${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(IMGUI_INCLUDE_DIR ${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(ASSIMP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dep/assimp)

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

add_executable(MyEngine			Main.cpp 
	Application.hpp				Application.cpp
	Camera.hpp					Camera.cpp
	GetAppPath.hpp				GetAppPath.cpp
	GUI.hpp						GUI.cpp
	Importer.hpp				Importer.cpp
	IndexBuffer.hpp				IndexBuffer.cpp
	Inputs.hpp					Inputs.cpp
	Material.hpp				Material.cpp
	Mesh.hpp					Mesh.cpp
	MyTest.hpp					MyTest.cpp
	MyTestMesh3D.hpp			MyTestMesh3D.cpp
	MyTestClearColor.hpp		MyTestClearColor.cpp
	MyTestSkyBox.hpp			MyTestSkyBox.cpp
	MyTestTexture2D.hpp			MyTestTexture2D.cpp
	LightingTest.hpp			LightingTest.cpp
	MyTexture.hpp				MyTexture.cpp
	Renderer.hpp				Renderer.cpp
	Scene.hpp					Scene.cpp
	Shader.hpp					Shader.cpp
	Time.hpp					Time.cpp
	VertexArray.hpp				VertexArray.cpp
	VertexBuffer.hpp			VertexBuffer.cpp
	VertexBufferLayout.hpp
	OGLIncludes.hpp
	LoadShader.hpp
	stb_image.h
)
target_include_directories(MyEngine PRIVATE 
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(MyEngine PRIVATE SDL2main SDL2-static opengl32 glew imgui assimp)

add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/resources/shaders $<TARGET_FILE_DIR:MyEngine>/shaders)

add_dependencies(MyEngine copy_shaders)

add_library(imgui STATIC ${IMGUI_SRCS})
target_include_directories(imgui PRIVATE 
  ${IMGUI_DIR}
  ${SDL_INCLUDE_DIR}
)

if(${IMGUI_USE_OGL3})
target_link_libraries(imgui glew)
endif()

set_property(TARGET MyEngine PROPERTY CXX_STANDARD 17)