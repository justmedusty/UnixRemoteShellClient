//

// Created by dustyn on 4/17/24.
//
#include <netdb.h>
#include "sys/socket.h"
#include "stdlib.h"
#include "stdio.h"
#ifndef UNIXREMOTESHELLCLIENT_CLIENT_SOCKET_INIT_H
#define UNIXREMOTESHELLCLIENT_CLIENT_SOCKET_INIT_H
int get_socket(char addr[],char port[]);
#endif //UNIXREMOTESHELLCLIENT_CLIENT_SOCKET_INIT_H
