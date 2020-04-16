#include <fcntl.h>
#include <unistd.h>

#include "application_state_client.hpp"
#include "common.h"

ApplicationStateClient::ApplicationStateClient()
{
    asc_fd_ = ::open(APPSTATE_SERVER_FIFO, O_WRONLY);
    if (asc_fd_ == -1)
        exit_error("ApplicationStateClient: FIFO open() failure");
}

ApplicationStateClient::~ApplicationStateClient()
{
    ::close(asc_fd_);
}

void ApplicationStateClient::ReportApplicationState(ApplicationState state)
{
    if (::write(asc_fd_, &state, sizeof(state)) != sizeof(state))
        exit_error("ApplicationStateClient: FIFO write() failure");
}