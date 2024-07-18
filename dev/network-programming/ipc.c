#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

void read_childproc(int sig);
void handle_childproc(int * fds, int retval);

int main() {
    /* Handle child termination*/
    struct sigaction sa;
    sa.sa_handler = read_childproc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGCHLD, &sa, 0);

    /* Parent scope */
    /* Create a child process and IPC1 */
    int ptoch1[2];
    pipe(ptoch1);
    pid_t ch1 = fork();
    if (ch1 == 0) {
        /* Child 1 scope */
        handle_childproc(ptoch1, 1);
    } else {
        /* Parent scope */
        /* Create child2 process and IPC2 */
        int ptoch2[2];
        pipe(ptoch2);
        pid_t ch2 = fork();
        if (ch2 == 0) {
            /* Child 2 scope */
            handle_childproc(ptoch2, 2);
        } else {
            /* Parent scope */
            char * msg = "Hi to child 1\n.";
            write(ptoch1[1], msg, strlen(msg));
            
            msg = "Hello to child 2\n.";
            write(ptoch2[1], msg, strlen(msg));

            /* Zombie process handling */
            sleep(10);
            exit(0);
        }
    }
}

void handle_childproc(int * fds, int retval) {
    /**
     * Read message from fds 
     * when '.' is typed, exit with retval
     */
    char c;
    while (read(fds[0], &c, 1) > 0 && c != '.') 
        printf("%c", c);
    exit(retval);
}

void read_childproc(int sig) {
    /* Read status code */
    int status;
    pid_t ch = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("A child process (pid: %d) exited with status code %d\n", ch, WEXITSTATUS(status));
    }
}