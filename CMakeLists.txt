# CMakeLists.txt
cmake_minimum_required(VERSION 3.2)
project (Snake)

set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-12)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -g")

add_executable(snake
               game.cpp
               main.cpp
               snake.cpp
               random.cpp
)

# If TermOx is cloned into a directory named 'external/', put 'external/TermOx' 
add_subdirectory(TermOx)
target_link_libraries(snake TermOx)