//
// Created by dustyn on 4/17/24.
//

#include <unistd.h>
#include <string.h>
#include "client_socket_init.h"

/*
 * A simple function for getting a server socket open and connected,  takes
 * addr and port as args which will be used to initalize the socket.
 */
int get_socket(char addr[],char port[]){
    struct addrinfo hints,*results, *pointer;
    int serverFd;
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int result;

    result = getaddrinfo(addr, port, &hints, &results);

    if(result != 0){
        fprintf(stderr,"Error getting addr info %s\n", gai_strerror(result));
        exit(EXIT_FAILURE);
    }

    for(pointer = results;pointer != NULL;pointer = pointer->ai_next){

        serverFd = socket(pointer->ai_family, pointer->ai_socktype, pointer->ai_protocol);
        if(serverFd == -1){
            perror("socket");
            continue;
        }

        if((connect(serverFd,pointer->ai_addr,pointer->ai_addrlen)) == -1){
            close(serverFd);
            perror("connect");

        }
        printf("%d\n",serverFd);
        break;
    }

    if(pointer == NULL){
        perror("connect");
        exit(EXIT_FAILURE);
    }



    freeaddrinfo(results);

    return serverFd;

}