/*
*   server.c
*   server implimentation
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#include "server.h"
#include "log.h"
#include "network.h"

//Currently, a trivial echo server
//Any information sent is trivially sent back :O
void server_loop() {
    socket_t server;
    socket_t client;

    if ((server = TCPServer("6660")) == -1) {
        chilog(CRITICAL, "server_loop: unable to intiate socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof their_addr;

    client = accept(server, (struct sock_addr*) &their_addr, &addr_size);
    if (client == -1) {
        chilog(CRITICAL, "server_loop: unable to established client connection");
        close(server);
        exit(EXIT_FAILURE);
    }

    // Now
    char print_buffer[1024] = {0};
    char buffer[512] = {0};
    Buffer sendbuf; 
    sendbuf.length=0;
    sendbuf.content=NULL;
    int current = 0;
    for (;;){
        current = recv(client, buffer, 512,0);
        if (current == -1) {
            chilog(ERROR, "server_loop: got error on recv()");
            return;
        }
        //Sucessfuly send the info
        sendbuf.length = current;
        sendbuf.content = buffer;
        TCPSend(client, &sendbuf);
        
        // Now, zero out the appropriate fields
        sendbuf.length=0; 
        sendbuf.content=NULL;
        current = 0;
        memset(&buffer, 0, sizeof(buffer));
    }

    close(client);
    close(socket);
}