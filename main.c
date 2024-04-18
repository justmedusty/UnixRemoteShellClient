#include <stdio.h>
#include <pty.h>
#include <unistd.h>
#include <sys/wait.h>
#include "client_socket_init.h"

int main(int argc, char *argv[]) {

    int socket_fd;
    int master, slave;
    char buf[2048];
    ssize_t num_bytes;
    pid_t pid;

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


        close(master);
        dup2(slave, 0);
        dup2(slave, 1);
        dup2(slave, 2);
        close(slave);
        execl("/bin/bash", "/bin/bash", NULL);
        perror("execl");
        exit(EXIT_FAILURE);

    }else{
        close(slave);
        while((num_bytes = read(master,buf,sizeof (buf))) > 0){
            write(STDOUT_FILENO,buf,num_bytes);
        }

        wait(NULL);
    }


    return 0;
}
