#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 100

void error_handling(char * err_msg) {
    puts(err_msg);
    exit(1);
}

int main(int argc, char * argv[]) {
    int serv_sock, client_sock;
    struct sockaddr_in serv_addr = {0}, client_addr = {0};
    struct timeval timeout;
    fd_set fds, copy_fds;

    socklen_t addr_size;
    int fd_max, str_len, fd_num, i;
    char buf[BUFSIZE];
    if (argc != 2) {
        printf("Usage: %s <PORT-NUMBER>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serv_sock, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
        error_handling("bind() error!");
    if (listen(serv_sock, 3) < 0)
        error_handling("listen() error!");
    
    FD_ZERO(&fds);
    FD_SET(serv_sock, &fds);
    fd_max = serv_sock + 1;

    while (1) {
        copy_fds = fds;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        if ((fd_num = select(fd_max, &copy_fds, 0, 0, &timeout)) == -1)
            break;
        
        if (fd_num == 0)
            continue;

        for (int i = 0; i < fd_max; i++) {
            if (FD_ISSET(i, &copy_fds)) { // is i-th fd the one observed
                if (i == serv_sock) { // connection request
                    addr_size = sizeof(client_addr);
                    client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &addr_size);
                    FD_SET(client_sock, &fds);
                    if (fd_max <= client_sock)
                        fd_max = client_sock + 1;
                    printf("New client connected: %d\n", client_sock);
                } else { // client sending message
                    str_len = read(i, buf, BUFSIZE); 
                    if (str_len == 0) {
                        FD_CLR(i, &fds);
                        close(i);
                        printf("Closed client connection: %d\n", i);
                    } else {
                        buf[str_len] = 0;
                        printf("Received message from client (%d): %s", i, buf);
                        write(i, buf, str_len);
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}