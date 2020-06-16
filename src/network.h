/**
 *  network.h
 *  interface for network programming
 * 
 * Types:
 *  socket_t: an alias for an int to represent a socket fd
 *  Buffer: a variable length struct used to hold information for sending messages;
 * 
 * Functions:
 *  TCPServer(): a function that creates a socket_fd and connects it to a given Host and Port;
 *          todo - perhaps it should return an errorcode instead?
 *          todo - needs a better function signature
 *  TCPConnection(): a function that creates a (client) connection to a particular host and port/service
 *          todo - signature
 *  TCPEnd(): a function that shutdowns and terminates a socket
 *  TCPSend(): a function that takes a Buffer and send all of the information in it
 * 
 * 
 */

#ifndef CHIRC_NETWORK_H_
#define CHIRC_NETWORK_H_

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

typedef int socket_t;

// todo switch this to it's own header file?
// Maybe a fn (s: [Char], out: &Buffer)->bool?
typedef struct {
    int length;     // Length of content[]
    char* content; // Data
} Buffer;

// TCP create connections
socket_t TCPServer(char* port);
socket_t TCPConnection();

// TCP sendall information
bool TCPSend(socket_t socket, Buffer* message);

//Convnience access to various standard functions
extern ssize_t recv(int s, void *buf, size_t len, int flags);
extern ssize_t send(int s, const void *buf, size_t len, int flags);
extern int close(int s);
#endif