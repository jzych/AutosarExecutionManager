#ifndef AS_TRAINING_APPLICATION_STATE_CLIENT_HPP_
#define AS_TRAINING_APPLICATION_STATE_CLIENT_HPP_

#include <cstdint>

enum class ApplicationState : uint8_t { kInitializing = 0, kRunning, kShuttingdown };

class ApplicationStateClient
{
public:
    ApplicationStateClient();

    ~ApplicationStateClient();

    void ReportApplicationState(ApplicationState state);
private:
    int asc_fd_;
};

#endif // !AS_TRAINING_APPLICATION_STATE_CLIENT_HPP_