/*
*   server.c
*   server implimentation
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "server.h"
#include "log.h"

void server_loop() {
    //Setup socket while being sure to check for error number;

    int server_fd, client_fd;
    char message_buffer[512] = {0};
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    // Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        chilog(CRITICAL, "Socket was not able to be established: Errno %s.", errno);
        exit(EXIT_FAILURE);
    }
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(6660);

    // Bind
    if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0){
        chilog(CRITICAL, "Socket was unable to be bound.");
        exit(EXIT_FAILURE);
    } else {
        chilog(DEBUG, "Sucessfuly binded!"); 
    }
    // Listen
    listen(server_fd, 5);
    chilog(DEBUG, "Successfully listened!");

    //Accept
    client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*) addrlen);
    if (client_fd < 0) {
        chilog(CRITICAL, "Accept failed.");
        exit(EXIT_FAILURE);
    }
}