project(arcade_ncurses)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -lncurses -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../../.lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./../..")

set(ncurses_SRC ncurses.cpp)
add_library(_arcade_ncurseslib SHARED ${ncurses_SRC})
