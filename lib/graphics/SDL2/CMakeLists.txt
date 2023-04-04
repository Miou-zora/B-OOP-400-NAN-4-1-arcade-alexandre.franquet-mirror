project(arcade_sdl2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -lSDL2 -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../../.lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./../..")

set(SDL2_SRC sdl2.cpp)
add_library(_arcade_sdl2lib SHARED ${SDL2_SRC})
