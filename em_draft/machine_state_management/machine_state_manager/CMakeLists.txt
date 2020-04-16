set (SRC
    src/machine_state_manager.cpp)

add_library(${machine_state_manager_lib} ${SRC})
target_link_libraries(${machine_state_manager_lib} ${machine_state_client})
target_include_directories(${machine_state_manager_lib} PUBLIC
        inc
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/machine_state_management/machine_state_client/inc)