cmake_minimum_required(VERSION 3.10)
project(SDLEngine)

# Keressük az SDL2-t
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

# Minden cpp fájl a src/ könyvtárból
file(GLOB SOURCES "src/*.cpp")

# Készítsünk egy futtatható fájlt
add_executable(SDLEngine ${SOURCES})

# Linkeljük az SDL2-t
target_link_libraries(SDLEngine ${SDL2_LIBRARIES})
