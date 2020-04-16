set (SRC
    src/machine_state_client.cpp)

add_library(${machine_state_client_lib} ${SRC})
target_include_directories(${machine_state_client_lib} PUBLIC
        inc
        ${PROJECT_SOURCE_DIR}/common/)