project(arcade_snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -W -pedantic -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}../../")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./../..")

set(SnakeSource snake.cpp)
add_library(arcade_snake SHARED ${SnakeSource})
set_target_properties(arcade_snake PROPERTIES PREFIX "")
