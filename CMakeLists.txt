project(MyEngine)

add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)

add_executable(MyEngine main.cpp)
target_include_directories(MyEngine PRIVATE ${SDL_INCLUDE_DIR})
target_link_libraries(MyEngine PRIVATE SDL2main SDL2-static opengl32)