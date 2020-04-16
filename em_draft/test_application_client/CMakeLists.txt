set (SRC
    src/test_application_client.cpp)

add_library(${test_application_client_lib} ${SRC})
target_include_directories(${test_application_client_lib} PUBLIC
        inc
        ${PROJECT_SOURCE_DIR}/application_state_client/inc
        ${PROJECT_SOURCE_DIR}/common)

target_link_libraries(${test_application_client_lib} ${application_state_client_lib})