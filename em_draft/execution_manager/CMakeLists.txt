set (SRC
    src/execution_manager.cpp)

add_library(${execution_manager_lib} ${SRC})
target_include_directories(${execution_manager_lib} PUBLIC
        inc
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/application_state_client/inc)