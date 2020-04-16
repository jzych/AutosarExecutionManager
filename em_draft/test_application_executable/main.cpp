#include <iostream>
#include <unistd.h>

#include "common.h"
#include "test_application_client.hpp"

void exit_handler()
{
    std::cout << "Test application cleanup... pid = " << getpid() << '\n';
    sleep(1);
}

int main(int argc, char* argv[])
{
    atexit(exit_handler);

    {
        ApplicationStateClient asc;
        SimpleApplication simplApp(asc);
        simplApp.run();
    }

    return static_cast<uint8_t>(ProcessState::Terminated);
    // calling _exit does NOT cause calls to exit handlers or buffers flush
    //_exit(static_cast<uint8_t>(ApplicationState::kShuttingdown));
}