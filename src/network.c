/**
 * network.c
 * implementation of network.h
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#include "log.h"
#include "network.h"

socket_t TCPServer(char* port) {
    socket_t server;
    struct addrinfo hints; // hints for getadddrinfo()
    struct addrinfo* servinfo; // pointer to results
    

    // Initialize hints 
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    int status;

    if ((status = getaddrinfo(NULL, port, &hints, &servinfo )) != 0){
        chilog(ERROR, "TCPServer() getaddrinfo() error: %s", gai_strerror(status));
    }

    // This will iterate over the linked list in servinfo and bind to the appropriate one
    struct addrinfo* ptr;
    for (ptr = servinfo; ptr != NULL; ptr = ptr->ai_next) {
        // Try to connect to server, continue if this is invalid
        if ((server = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol))== -1) {
            chilog(DEBUG, "TCPServer() failed socket() attempt, retrying");
            continue;
        }

        // If socket sucessfuly initiated, then try and bind it to the gotten information
        if (bind(server, ptr->ai_addr, ptr->ai_addrlen) == -1) {
            chilog(DEBUG, "TCPServer() failed bind() attempt, retrying");
            close(server);
            continue;
        }

        break;
    }

    if (ptr == NULL) {
        // if we're here, we've looped to the end of the list but found no successful information
        chilog(ERROR, "TCPServer() failed to bind socket correctly");
        return -1;
    }
    // free addrinfo, since we're done with it
    freeaddrinfo(servinfo);

    // Noew, start listen()
    if (listen(server, 10) == -1) {
        int saved_errno = errno;
        switch(saved_errno){
            // Is this overkill? very likely
            case ENOBUFS:
            case ENOMEM:
                chilog(ERROR, "TCPServer() No buffer space available for listen()");
                return -1;
            case EACCES:
                chilog(ERROR, "TCPServer() process did not have permission to listen()");
                return -1;
            case EOPNOTSUPP:
                chilog(ERROR, "TCPServer protocol does not support listen()");
                return -1;
            default:
                chilog(ERROR, "TCPServer() something went wrong while listening");
                return -1;
        }
    }
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
