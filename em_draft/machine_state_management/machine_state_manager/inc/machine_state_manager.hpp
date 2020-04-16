#ifndef AS_TRAINING_MACHINE_STATE_MANAGER_HPP_
#define AS_TRAINING_MACHINE_STATE_MANAGER_HPP_

#include "machine_state_client.hpp"

class MachineStateManager
{
public:
    MachineStateManager(std::string appName);
    ~MachineStateManager();

    StateError get_machine_state(std::string& state, uint32_t timeout);
    StateError request_machine_state(std::string state, uint32_t timeout);

private:
    MachineStateClient msc_;
};

#endif // !AS_TRAINING_MACHINE_STATE_MANAGER_HPP_