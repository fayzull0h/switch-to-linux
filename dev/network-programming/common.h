#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_IP "10.0.0.205"
#define SERVER_PORT 12345

int socket_file_descriptor();

void setup_socket_address(struct sockaddr_in * address, char * ip, int port);

void make_zero(char * arr, int len);
