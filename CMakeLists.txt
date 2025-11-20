cmake_minimum_required(VERSION 3.10)
project(SDLEngine)


find_package(SDL2 REQUIRED)
find_library(SDL2_GFX_LIB SDL2_gfx)

include_directories(${SDL2_INCLUDE_DIRS} include)
file(GLOB SOURCES "src/*.cpp")
add_executable(SDLEngine ${SOURCES})
target_link_libraries(SDLEngine ${SDL2_LIBRARIES} ${SDL2_GFX_LIB})

