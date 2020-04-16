#include <fcntl.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <unistd.h>

#include "application_state_client.hpp"
#include "common.h"
#include "execution_manager.hpp"

#define INVALID_STATE 10;

void print_child_status(int status);

ExecutionManager::ExecutionManager()
{
    fifo_fd_ = ::open(APPSTATE_SERVER_FIFO, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
    if (fifo_fd_ == -1) {
        // TODO: implement exception handling
        exit_error("ExecutionManager: FIFO open() failure");
    }
}

ExecutionManager::~ExecutionManager()
{
    ::close(fifo_fd_);
}

void ExecutionManager::exec_process(char* path)
{
    pid_t pid;

    char* basename = strrchr(path, '/');
    if (basename != nullptr)
        ++basename;
    else
        basename = path;

    char* process_argv[2] = {basename, nullptr};

    // TODO: here shall be passed path and arguments of an application
    // received from application manifest

    switch (pid = fork()) {
    case -1:
        exit_error("Execution Manager: fork() failure (-1)");
    case 0:
        process_map_[pid] = INVALID_STATE;
        execv(path, process_argv);
    default:
        break;
    }
}

void ExecutionManager::listen_for_process_state_change()
{
    uint8_t buffer;
    int bytes_read;

    // TODO:: exceptions handling
    while ((bytes_read = read(fifo_fd_, &buffer, sizeof(uint8_t)) > 0)) {
        if (bytes_read == sizeof(uint8_t))
            std::cout << "EM: state report received. Current status state: "
                      << std::to_string(static_cast<uint8_t>(buffer)) << '\n';
        else
            exit_error("ExecManager: FIFO read() - wrong amount of bytes readed");
    }
    if (bytes_read == -1)
        exit_error("ExecManager: FIFO read() failure(-1)");
}

void ExecutionManager::wait_for_process()
{
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0)
        print_child_status(status);
}

void ExecutionManager::run()
{
    int const MAX_EVENTS = 10;
    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];

    int epfd = epoll_create1(0);

    ev.data.fd = fifo_fd_;
    ev.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fifo_fd_, &ev) == -1)
        exit_error("ExecManager: epoll_ctl() filaure(-1)");

    char* path = "../build/test_application_executable/TEST_EXECUTABLE";
    std::cout << "Launching process...\n";
    exec_process(path);
    for (;;) {
        int ready = epoll_wait(epfd, &ev, MAX_EVENTS, 1000);
        if (ready == -1)
            exit_error("ExecManager: epoll_wait() failure(-1)");

        if (ev.events & EPOLLIN) {
            listen_for_process_state_change();
        }
        else if (ev.events & (EPOLLHUP | EPOLLERR)) {
            // FIFO write end has been closed on the write side (ASC); what to do?
        }
        else {
            strerror(errno);
        }

        wait_for_process();
        std::cout << "Doing some ExecManager work...\n";
    }
}

void print_child_status(int status)
{
    uint8_t child_exit_status = 0;
    if (WIFEXITED(status)) {
        child_exit_status = static_cast<uint8_t>(WEXITSTATUS(status));
        if (child_exit_status == static_cast<uint8_t>(ProcessState::Terminated))
            std::cout << "Child closed properly. Exit status: "
                      << std::to_string(static_cast<uint8_t>(child_exit_status)) << '\n';
        else {
            // TODO: implement error handling
            std::cerr << "Child exited with unexpected code status: "
                      << std::to_string(static_cast<uint8_t>(child_exit_status)) << '\n';
        }
    }
    else if (WIFSIGNALED(status)) {
        std::cout << "Child killed by a singnal " << WTERMSIG(status) << '('
                  << strsignal(WTERMSIG(status)) << ')';
#ifdef WCOREDUMP
        if (WCOREDUMP(status))
            std::cout << " (core dumped)";
#endif
        std::cout << '\n';
    }
    else if (WIFSTOPPED(status)) {
        std::cout << "Child stopped by a signal " << WSTOPSIG(status) << '('
                  << strsignal(WSTOPSIG(status)) << ")\n";
#ifdef WIFCONTINUED
    }
    else if (WIFCONTINUED(status)) {
        std::cout << "Child continued.\n";
#endif
    }
    else {
        std::cerr << "Unexpected error in child; (status = " << static_cast<unsigned>(status)
                  << ")\n";
    }
}