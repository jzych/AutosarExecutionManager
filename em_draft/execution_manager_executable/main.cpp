#include <iostream>

#include <unistd.h>

#include <limits.h>
#include <string.h>
#include <sys/wait.h>

#include "application_state_client.hpp"
#include "execution_manager.hpp"

int main(int argc, char* argv[])
{
    std::cout << "Start of main; PID = " << getpid() << '\n';

    ExecutionManager em;
    em.run();

    /*  CAUTION!
        For now program is interrupted by singal due to endless for loop being implemented.
        Just be sure to close FIFO fd when EM is implemented in the class form.
    */
    std::cout << "End of main\n";

    return 0;
}