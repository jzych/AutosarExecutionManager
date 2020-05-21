#include <stdio.h>
#include <stdbool.h>

bool shall_succeed = true;

struct sockaddr {};
typedef unsigned int socklen_t;

int wrappers_subroutine(char const* msg)
{
    printf("%s",msg);
    if (shall_succeed)
        return 0;
    return -1;
}

int __wrap_socket()
{
    return wrappers_subroutine("__wrap_socket\n");
}

int __wrap_close()
{
    return wrappers_subroutine("__wrap_close\n");
}

int __wrap_remove()
{
    return wrappers_subroutine("__wrap_remove\n");
}

int __wrap_bind()
{
    return wrappers_subroutine("__wrap_bind\n");
}

int __wrap_listen()
{
    return wrappers_subroutine("__wrap_listen\n");
}

int __wrap_accept()
{
    return wrappers_subroutine("__wrap_accept\n");
}

int __wrap_connect()
{
    return wrappers_subroutine("__wrap_connect\n");
}