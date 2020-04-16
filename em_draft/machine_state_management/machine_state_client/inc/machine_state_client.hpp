#ifndef AS_TRAINING_MACHINE_STATE_CLIENT_HPP_
#define AS_TRAINING_MACHINE_STATE_CLIENT_HPP_

#include <string>

enum class StateError : uint8_t;
class MachineStateClient
{
public:
    MachineStateClient(std::string path = "");
    ~MachineStateClient();

    StateError register_app(std::string appName, uint32_t timeout);
    StateError get_machine_state(std::string &state, uint32_t timeout);
    StateError set_machine_state(std::string state, uint32_t timeout);

private:
    int msc_fd_;
};

#endif // !AS_TRAINING_MACHINE_STATE_CLIENT_HPP_