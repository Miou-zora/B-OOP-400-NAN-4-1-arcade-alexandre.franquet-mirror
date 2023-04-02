project(arcade_sfml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -lsfml-graphics -lsfml-window -lsfml-system -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../.lib")

set(SFML_SRC sfml.cpp)
add_library(_arcade_sfmllib SHARED ${SFML_SRC})
