cmake_minimum_required(VERSION 3.9)
project(Nibbler)

#set(CMAKE_CXX_STANDARD 11 "${CMAKE_CXX_FLAGS} -L ~/.brew/lib -lSDL2 -lSDL2_ttf -lSDL2_image")
#set(g++ -L ~/.brew/lib -lSDL2 -lSDL2_ttf -lSDL2_image -I ~/.brew/include/SDL2/ -D_THREAD_SAFE)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SDL2_INCLUDE_DIR /Users/kmykhail/.brew/include/SDL2)
set(SDL2_LIBRARY /Users/kmykhail/.brew/lib)


include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDL_LIBRARY})
set(SOURCE_FILES main.cpp)

add_executable(Nibbler ${SOURCE_FILES})

#target_link_libraries(Nibbler ${SDL2_LIBRARY})
target_link_libraries(Nibbler ${SDL_LIBRARY})
target_include_directories(Nibbler PRIVATE ${SDL2_INCLUDE_DIR})
