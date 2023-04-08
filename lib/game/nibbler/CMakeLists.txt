project(arcade_nibbler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -fPIC")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../../")

set(NibblerSource nibbler.cpp)
add_library(arcade_nibbler SHARED ${NibblerSource})
set_target_properties(arcade_nibbler PROPERTIES PREFIX "")
