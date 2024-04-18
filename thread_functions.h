//
// Created by dustyn on 4/18/24.
//
#include <unistd.h>



#include "pthread.h"
#include "sys/socket.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef UNIXREMOTESHELLCLIENT_THREAD_FUNCTIONS_H
#define UNIXREMOTESHELLCLIENT_THREAD_FUNCTIONS_H
void *thread_function(void* socket_fd);
#endif //UNIXREMOTESHELLCLIENT_THREAD_FUNCTIONS_H
