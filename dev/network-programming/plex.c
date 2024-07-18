#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char * argv[]) {
    fd_set fds, copyfds;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&fds);
    FD_SET(0, &fds); // 0 is stdin

    while (1) {
        copyfds = fds;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        result = select(1, &copyfds, 0, 0, &timeout);
        if (result == -1) {
            puts("select() error!");
            break;
        } else if (result == 0) {
            puts("Time out!");
        } else {
            if (FD_ISSET(0, &copyfds)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("Message typed: %s", buf);
            }
        }
    }
    return 0;
}