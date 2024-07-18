#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

void error_handling(char * msg);

int main(int argc, char * argv[]) {
    /* Setup */
    int sock;
    char msg[BUFSIZE];
    int str_len;
    struct sockaddr_in serv_addr = {0};

    if (argc != 3) {
        printf("Usage: %s <IP> <PORT-NUMBER>\n", argv[0]);
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) error_handling("socket() error!");

    /* Set server address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &(serv_addr.sin_addr)) < 0) {
        printf("Failed to set address: %s\n", argv[1]);
        exit(1);
    }

    if (connect(sock, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("connect() error!");
    else
        puts("Connected...");

    /* Get input and write to server */
    while (1) {
        printf("Enter message (q to quit): ");
        fgets(msg, BUFSIZE, stdin);

        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
            break;
        
        str_len = write(sock, msg, strlen(msg));
        if (str_len == -1) error_handling("Could not send message!");

        str_len = read(sock, msg, BUFSIZE-1);
        if (str_len == -1) error_handling("Could not read message!");

        msg[str_len] = 0;
        printf("Message received: %s", msg);
    }
    close(sock);
    return 0;
}

void error_handling(char * msg) {
    puts(msg);
    exit(2);
}