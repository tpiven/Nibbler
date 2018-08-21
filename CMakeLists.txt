cmake_minimum_required(VERSION 3.9)
project(Nibbler)

set(CMAKE_CXX_STANDARD 11)
set(SDL2_INCLUDE_DIR ~/.brew/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/lib/)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY})

add_executable(Nibbler main.cpp Game_sdl.hpp Game_sdl.cpp)

target_link_libraries(Nibbler -lSDL2 -lSDL2_image)