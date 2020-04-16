#ifndef AS_TRAINING_COMMON_H_
#define AS_TRAINING_COMMON_H_

#include <cstdint>
#include <iostream>

#include <fcntl.h>

#define APPSTATE_SERVER_FIFO "/usr/run/execution-manager/appstate-server-fifo"
#define MACHINESTATE_SERVER_FIFO "/usr/run/exectuion-manager/machinestate-server-fifo"

enum class ProcessState : uint8_t { Idle = 0, Starting, Running, Terminating, Terminated };
enum class StateError : uint8_t { kSuccess = 0, kInvalidState, kInvalidRequest, kTimeout };

inline void exit_error(char const* msg)
{
    if (msg != nullptr)
        std::cerr << msg << '\n';
    exit(EXIT_FAILURE);
}

#endif  // !AS_TRAINING_COMMON_H_