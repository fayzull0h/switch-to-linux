#include "common.h"

int main (int argc, char ** argv) {
    /** Setup
     * sockfd - socket file descriptor
     * servaddr - socket address for the server
    */
    int sockfd = socket_file_descriptor();
    struct sockaddr_in servaddr = {0};
    setup_socket_address(&servaddr, "https://good-generally-sailfish.ngrok-free.app", 80);
    socklen_t addr_size = sizeof(servaddr);
/*
    // Get username
    char * username;
    size_t username_size = 0;
    printf("Username: ");
    int username_len = getline(&username, &username_size, stdin);
    username[username_len - 1] = ':';

    // Get messages and send to server
    while(1) {
        // Get the message
        char * msg;
        size_t msg_size = 0;
        int msg_len = getline(&msg, &msg_size, stdin);

        // Check if exit
        if (strcmp(msg, "exit\n") == 0) {
            free(msg);
            break;
        }

        // Construct message to send
        char * final_msg = malloc(sizeof(char) * (username_len + msg_len));
        strcpy(final_msg, username);
        strcpy(final_msg + username_len, msg);

        // Send the message
        sendto(sockfd, final_msg, username_len + msg_len, 0, (const struct sockaddr * )&servaddr, addr_size);
        
        // Free memory
        free(msg);
        free(final_msg);
    }*/


    // Receive messages from server
    char msg[1024] = {0};
    recvfrom(sockfd, msg, 1024, 0, (struct sockaddr *)&servaddr, &addr_size);
    printf("%s", msg);

    close(sockfd);
    // free(username);
    return 0;
}

