#include "common.h"

int main(int argc, char ** argv) {
    // Create socket handle
    int sockfd = socket_file_descriptor();

    /** Setup
     * server_address - stores the address of this program (the server)
     * client_address - stores the address of the 
    */
    struct sockaddr_in server_address = {0};
    struct sockaddr_in client_address = {0};
    setup_socket_address(&server_address, "", SERVER_PORT);
    socklen_t address_size;

    // Binding the socket to the server address
    int bind_result = bind(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address));
    if (bind_result != 0) {
        perror("ERROR: Failed to bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else printf("Bind successful\n");

    // Receive a message from the client
    char buffer[1024] = {0};
    while(1) {
        make_zero(buffer, 1024);
        address_size = sizeof(client_address);
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_address, &address_size);

        printf("Received from local: %s", buffer);

        char message[1024] = {0};
        strcpy(message, "Fayzulloh: ");
        strcpy(message + 11, buffer);
        sendto(sockfd, message, 1024, 0, (const struct sockaddr *)&client_address, address_size);
    }

    close(sockfd);
    return 0;
}