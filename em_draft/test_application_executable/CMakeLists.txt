set (EXEC_NAME "TEST_EXECUTABLE")

add_executable(${EXEC_NAME} main.cpp)
target_link_libraries(${EXEC_NAME}
        ${test_application_client_lib})