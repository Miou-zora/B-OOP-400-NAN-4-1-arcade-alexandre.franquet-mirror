project(arcade_debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../.lib")

set(DEBUG_SRC Debug.cpp)
add_library(_arcade_debuglib SHARED ${DEBUG_SRC})
