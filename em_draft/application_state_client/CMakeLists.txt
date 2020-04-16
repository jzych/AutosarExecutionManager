set (SRC
    src/application_state_client.cpp)

add_library(${application_state_client_lib} ${SRC})
target_include_directories(${application_state_client_lib} PUBLIC
        inc
        ${PROJECT_SOURCE_DIR}/common/)