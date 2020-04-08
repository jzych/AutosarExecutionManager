cmake_minimum_required(VERSION 3.10)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                ${CMAKE_BINARY_DIR}/googletest-build
                EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed.

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "-g -O0 --coverage")

project(AutosarEM)

file(GLOB SOURCES
    inc/*.hpp
    src/*.cpp
)

add_executable(AutosarEM ${SOURCES})
target_link_libraries(AutosarEM pthread)
target_include_directories(AutosarEM PRIVATE inc/)
target_compile_options(AutosarEM PRIVATE -Wall -Werror -Wpedantic -Wextra)

file(GLOB TEST_SOURCES
    inc/*.hpp
    src/*.cpp
    test/*.cpp
)
list(FILTER TEST_SOURCES EXCLUDE REGEX ".*src/main.cpp$")

link_libraries(gtest)
add_executable(${PROJECT_NAME}-ut ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}-ut PRIVATE inc/)
