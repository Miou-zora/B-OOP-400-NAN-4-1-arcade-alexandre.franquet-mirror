project(arcade_ncurses)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -lncurses -fPIC")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../../")

set(ncurses_SRC ncurses.cpp)
add_library(arcade_ncurses SHARED ${ncurses_SRC})
set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
