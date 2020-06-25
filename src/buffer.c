/**
 * buffer.c
 * 
 * Buffer implementation
*/
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "log.h"
#include "buffer.h"

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
        char* chars = calloc(size, sizeof(char));
        if (chars == NULL && errno == ENOMEM){
            chilog(CRITICAL, "BufNew: Out of memory, exiting");
            exit(EXIT_FAILURE);
        }
        errno=stored_error;
    }
    
    buffer->capacity = size;
    buffer->data = chars;

}

int BufSub(Buffer* buffer, char* string) {
    int buf_len = buffer->length;
    int str_len = strlen(string);
    if (buf_len == 0 || str_len == 0) {
        chilog(DEBUG, "BufSub: buffer or substring is 0");
        return -1;
    }
    if (str_len > buf_len) {
        chilog(DEBUG, "BufSub: substring to search for is larger than buffer");
        return -1;
    }

    for (int index=0; index < buf_len-str_len; index ++) {
        /*
        By using strlen()'s result, we assure we won't compare the terminating bull byte of string
        */
        if (memcmp(&(buffer->data[index]), string, str_len) ==0) {
            return index;
        }
    }
    return -1;
}

void BufFree(Buffer* buffer){
    free(buffer->data);
    BufInit(buffer);
}

void BufClear(Buffer* buffer){
    memset(buffer->data, 0,sizeof(char)*buffer->capacity);
    buffer->length = 0;
}