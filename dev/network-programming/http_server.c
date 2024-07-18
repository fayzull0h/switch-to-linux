#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    FILE * index = fopen("index.html", "r");
    char file_data[1024];
    fgets(file_data, 1024, index);
    char to_send[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(to_send, file_data);

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8001);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0) {
        printf("Failed to bind...\n");
        return 1;
    }

    if (listen(serv_sock, 5) != 0) {
        printf("Failed to listen...\n");
        return 1;
    }

    while (1) {
        int client_sock = accept(serv_sock, NULL, NULL);
        send(client_sock, to_send, sizeof(to_send), 0);
        close(client_sock);
    }
    return 0;
}