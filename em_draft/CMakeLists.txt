cmake_minimum_required(VERSION 3.10)
project(AS_TRAINING_PROJECT)

set(CMAKE_CXX_STANDARD 14)

if (NOT EXISTS "/usr/run/execution-manager/appstate-server-fifo")
    message(SEND_ERROR
            "Can not find appstate-server-fifo file in /usr/run/execution_manager;\
             be sure to run appstate_server_fifo_create.sh script")
endif()

set(application_state_client_lib "application_state_client_lib")
set(execution_manager_lib "execution_manager_lib")
set(machine_state_client_lib "machine_state_client_lib")
set(machine_state_manager_lib "machine_state_manager_lib")
set(test_application_client_lib "test_application_client_lib")

add_subdirectory(application_state_client)
add_subdirectory(execution_manager)
add_subdirectory(execution_manager_executable)
add_subdirectory(machine_state_management)
add_subdirectory(test_application_client)
add_subdirectory(test_application_executable)