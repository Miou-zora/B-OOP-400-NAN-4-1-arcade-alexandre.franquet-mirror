cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-ldl -Wall -Werror -Wextra -Wshadow -Wuninitialized -fPIC -fno-gnu-unique")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

####################CORE####################

set(INCLUDE_SRC core/src/Display
                core/src/Game/
                core/src/Game/snake
                core/src/Input
                core/src/Object
                core/src/Sounds
                core/src/Text
                core/src
                core/
)
include_directories(${INCLUDE_SRC})
add_subdirectory(tests/debug_lib)
add_subdirectory(lib/graphics)
add_subdirectory(lib)

project(arcade)

set(CORE_MAIN main.cpp)

set(CORE_SRC core/Core.cpp)


add_executable(arcade ${CORE_MAIN} ${CORE_SRC})


####################TESTS####################

set(CMAKE_CXX_FLAGS "-ldl -Wall -Werror -Wextra -Wshadow -Wuninitialized --coverage -lcriterion")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

enable_testing()
set(TEST_SRC tests/tests.cpp)

#add_executable(tests_run ${TEST_SRC} ${CORE_SRC})
#add_test(NAME tests_run COMMAND ./tests_run)
