/**
 * network.c
 * implementation of network.h
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>

#include "log.h"
#include "network.h"

socket_t TCPServer(char* port) {
    socket_t server;
    struct addrinfo hints; // hints for getadddrinfo()
    struct addrinfo* servinfo; // pointer to results
    struct addrinfo* pointer;

    // Initialize hints 
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    int status;

    if ((status = getaddrinfo(NULL, port, &hints, &servinfo )) != 0){
        chilog(ERROR, "getaddrinfo() error: %s\n", gai_strerror(status));
    }

    for (pointer = servinfo; pointer != NULL; pointer = pointer->ai_next) {

    }

    // final stuff to do
    freeaddrinfo(servinfo);

    return server;
}



bool TCPSend(socket_t socket, Buffer* message) {
    // Short circuits
    if (message->length == 0) {
        chilog(DEBUG, "TCPSend() socket %d: message is 0-bytes long");
        return false;
    }
    
    int remaining = message->length;
    int position = 0;
    int result=0;
    char* data = message->content;
    
    //Send data until it ends
    while (remaining != 0) {
        chilog(DEBUG, "TCPSend() socket %d: sending from %d-length message at position %d",
                socket,
                message->length,
                position);

        result = send(socket, data, message->length, 0);
        
        if (result == -1){
            chilog(ERROR, "Client socket: %d had an error", socket);
            return false;
        }

        chilog(DEBUG, "TCPSend() socket %d: successfuly sent %d bytes", socket, result);
    // Set information for next iteration

        remaining -= result;
        position += result;
        data = &data[position];
    }

    // Having finished sending all of our data, we return true
    return true;
}
