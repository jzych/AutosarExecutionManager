#include <unistd.h>

#include "common.h"
#include "machine_state_client.hpp"

MachineStateClient::MachineStateClient(std::string path)
{
    // if (path == "")
    //     msc_fd_ = open(MACHINESTATE_SERVER_FIFO,)
}

MachineStateClient::~MachineStateClient()
{
}

StateError MachineStateClient::register_app(std::string appName, uint32_t timeout)
{
}

StateError MachineStateClient::get_machine_state(std::string& state, uint32_t timeout)
{
}

StateError MachineStateClient::set_machine_state(std::string state, uint32_t timeout)
{
}