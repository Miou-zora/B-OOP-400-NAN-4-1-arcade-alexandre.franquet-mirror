project(arcade_sfml)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../.lib")

set(SFML_SRC Debug.cpp)
add_library(_arcade_debuglib SHARED ${SFML_SRC})