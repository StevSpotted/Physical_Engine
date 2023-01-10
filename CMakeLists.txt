
cmake_minimum_required(VERSION 3.13)
project(C_Projects C)
# use dynamic SDL2 libraries only
set(SDL2_USE_STATIC_LIBS OFF)
# ensure that SDL2 package is available
find_package(SDL2)

# includes all SDL2 includes directories
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_C_STANDARD 99)

#main file is compiled
add_executable(C_Projects main.c elements.c headers/elements.h update.c headers/update.h headers/define.h draw.c headers/draw.h init.c headers/init.h)
#Then, SDL2 libraries are linked ($SDL2_LIBRARIES Means -lSDL2)
target_link_libraries(C_Projects ${SDL2_LIBRARIES})
