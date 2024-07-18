#include "server.h"

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