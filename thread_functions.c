//
// Created by dustyn on 4/18/24.
//

#include "thread_functions.h"

void *thread_function(void* socket_fd) {

    ssize_t bytes_received;
    char buffer[2048];
    for (;;) {

        bytes_received = recv(*(int *) socket_fd, buffer, sizeof buffer, 0);
        if (bytes_received == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (bytes_received == 0) {
            printf("Hangup on socket %d\n", *(int *) socket_fd);
            exit(EXIT_SUCCESS);
        }

        write(STDOUT_FILENO, &buffer, sizeof bytes_received);

    }


}