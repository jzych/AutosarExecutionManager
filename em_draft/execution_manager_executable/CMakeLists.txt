set (EXEC_NAME "EM_EXEC")

add_executable(${EXEC_NAME} main.cpp)

target_link_libraries(${EXEC_NAME}
        ${application_state_client_lib}
        ${execution_manager_lib})