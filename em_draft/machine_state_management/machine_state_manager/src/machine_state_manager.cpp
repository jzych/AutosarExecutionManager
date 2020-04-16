#include "common.h"
#include "machine_state_manager.hpp"

constexpr uint32_t DEFAULT_TIMEOUT = 5000;

MachineStateManager::MachineStateManager(std::string appName) : msc_(MACHINESTATE_SERVER_FIFO)
{
    msc_.register_app(appName, DEFAULT_TIMEOUT);
}