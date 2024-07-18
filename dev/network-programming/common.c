#include "common.h"

void make_zero(char * arr, int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = 0;
    }
}

void setup_socket_address(struct sockaddr_in * address, char * ip, int port) {
    /* Setting destination
     * sin_family set to IPv4
     * htons configures the endianness properly
     * usd ports higher than 1000
     * INADDR_ANY = 0.0.0.0
    */
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = (ip[0]) ? inet_addr(ip) : INADDR_ANY;
    return;
}

int socket_file_descriptor() {
    /* Explanation: socket object
     * AF_INET - IPv4
     * SOCK_DGRAM - UDP packet signifier
     * 0 - protocol 0 for computer to know it's UDP
     * fd - file descriptor, socket() returns smth similar to a file handle
     */
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    // Error handling
    if (fd == -1) {
        perror("ERROR: Failed to create socket");
        exit(EXIT_FAILURE);
    }
    return fd;
}
