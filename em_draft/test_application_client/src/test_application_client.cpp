#include <unistd.h>
#include <iostream>

#include "test_application_client.hpp"

#define BUFFER_SIZE 512

SimpleApplication::SimpleApplication(ApplicationStateClient& asc) : asc_(asc)
{
    init();
}

SimpleApplication::~SimpleApplication()
{
    cleanup();
}

void SimpleApplication::run()
{
    std::cout << "Starting running procedure...\n";
    currentState_ = ApplicationState::kRunning;
    asc_.ReportApplicationState(currentState_);

    for (int i = 5; i > 0; --i) {
        std::cout << "Doing some work... " << i << " seconds left...\n";
        sleep(1);
    }

    std::cout << "Work finished\n";
}

void SimpleApplication::init()
{
    std::cout << "Starting init procedure...\n";
    currentState_ = ApplicationState::kInitializing;
    asc_.ReportApplicationState(currentState_);

    resource_ = new char[BUFFER_SIZE]{"I am the resource of the SimpleApplication.\n\0"};
    sleep(1);
    std::cout << resource_ << '\n';
}

void SimpleApplication::cleanup()
{
    std::cout << "Starting shutdown procedure\n";
    currentState_ = ApplicationState::kShuttingdown;
    asc_.ReportApplicationState(currentState_);
    std::cout << "Releasing resources...\n";
    sleep(1);
    delete[] resource_;
    std::cout << "Done!\n";
}