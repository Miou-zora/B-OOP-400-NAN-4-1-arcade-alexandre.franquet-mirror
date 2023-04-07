project(arcade_sdl2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -lSDL2main -lSDL2 -lSDL2_ttf -fPIC")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../../")

set(SDL2_SRC sdl2.cpp)
add_library(arcade_sdl2 SHARED ${SDL2_SRC})
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
