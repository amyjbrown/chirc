/**
 * buffer.c
 * 
 * Buffer implementation
*/
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "buffer.h"
#include "log.h"

//Sets stack elements to zero
static inline void BufInit(Buffer* buffer){
    buffer->length = 0;
    buffer->capacity = 0;
    buffer->data = NULL;
}

void BufNew(Buffer* buffer, unsigned int size) {
    if (size == 0) return;

    BufInit(buffer);
    char* chars;
    //Appropriate Error checking
    chilog(DEBUG, "BufNew: setting errno in anon block");
    {
        int stored_error=errno;
        errno=0;
        char* chars = calloc(size, sizeof char);
        if (chars == NULL && errno == ENOMEM){
            chilog(CRITICAL, "BufNew: Out of memory, exiting");
            exit(EXIT_FAILURE);
        }
        errno=stored_error;
    }
    
    buffer->capacity = size;
    buffer->data = chars;

}

void BufFree(Buffer* buffer){
    free(buffer->data);
    BufInit(buffer);
}

void BufClear(Buffer* buffer){
    memset(buffer->data, 0,sizeof(char)*buffer->capacity);
    buffer->length = 0;
}