project(arcade_sfml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -lsfml-graphics -lsfml-window -lsfml-system -fPIC")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../../")

set(SFML_SRC sfml.cpp)
add_library(arcade_sfml SHARED ${SFML_SRC})
set_target_properties(arcade_sfml PROPERTIES PREFIX "")
