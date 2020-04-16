#ifndef AS_TRAINING_TEST_APPLICATION_CLIENT_HPP_
#define AS_TRAINING_TEST_APPLICATION_CLIENT_HPP_

#include "application_state_client.hpp"

class SimpleApplication
{
public:
    explicit SimpleApplication(ApplicationStateClient& asc);
    ~SimpleApplication();

    void run();

private:
    void init();
    void cleanup();

private:
    char const* resource_;
    ApplicationStateClient& asc_;
    ApplicationState currentState_;
};

#endif  // !AS_TRAINING_TEST_APPLICATION_CLIENT_HPP_