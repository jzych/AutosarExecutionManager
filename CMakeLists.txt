cmake_minimum_required(VERSION 3.10)

# Download and unpack external dependecies at configure time
configure_file(CMakeLists.txt.in external/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external)
if(result)
    message(FATAL_ERROR "CMake step for externals failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external)
if(result)
    message(FATAL_ERROR "Build step for externals failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add external dependencies directly to our build.
add_subdirectory(${CMAKE_BINARY_DIR}/external/googletest-src
                ${CMAKE_BINARY_DIR}/external/googletest-build
                EXCLUDE_FROM_ALL)

add_subdirectory(${CMAKE_BINARY_DIR}/external/nlohmann_json-src
                ${CMAKE_BINARY_DIR}/external/nlohmann_json-build
                EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "-g -O0 --coverage")

project(AutosarEM)

file(GLOB EM_SOURCES
    main.cpp
    ara/exec/**/*.h
    ara/exec/**/*.cpp
    ara/core/*.h
    ara/com/*.h
    ara/com/*.cpp
)

add_executable(${PROJECT_NAME} ${EM_SOURCES})
target_link_libraries(${PROJECT_NAME} pthread nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ara/exec/ ara/exec/praser/ ara/com/ ara/core/)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic -Wextra)

file(GLOB TEST_SOURCES
    ara/exec/**/*.h
    ara/exec/**/*.cpp
    ara/core/*.h
    ara/com/*.h
    ara/com/*.cpp
    test/*.cpp
)

link_libraries(gtest)
add_executable(${PROJECT_NAME}-ut ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}-ut PRIVATE ara/exec/ ara/exec/parser/ ara/com/ ara/core/)
target_link_libraries(${PROJECT_NAME}-ut nlohmann_json)
