#ifndef AS_EXECUTION_MANAGER_H_
#define AS_EXECUTION_MANAGER_H_

#include <unordered_map>

class ExecutionManager
{
public:
    ExecutionManager();
    ~ExecutionManager();

    void exec_process(char* path);
    void listen_for_process_state_change();
    void wait_for_process();
    void run();

private:
    int fifo_fd_;
    std::unordered_map<pid_t, uint8_t> process_map_;
};

#endif  // !AS_EXECUTION_MANAGER_H_