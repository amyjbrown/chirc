/**
 * buffer.h
 * provides interface for buffers that are aware of their own sizes
 * Note that buffer is not necessarily a NUL-Terminated string 
 * Any conversion should go through the API
 * 
 * 
*/

#ifndef CHIRC_BUFFER_H_
#define CHIRC_BUFFER_H_H
/**
 * For example, the buffer(16) containg "Hello World!␀" would contain this
 * length: 13 [including the null]
 * capacity: 16 (contains some spare space)
 * data: &"Hello World␀" somewhere on the heap
*/
typedef struct {
    unsigned int length;     // Length of data stored in array
    unsigned int capacity;   // Total capacity of array
    char* data; // Heap-allocated data
} Buffer;

// Allocates a new Buffer on the heap
void BufNew(Buffer* buffer, unsigned int size);

//Deallocates the space of the buffer
void BufFree(Buffer* buffer);

//Find the first index of string in Buffer, or -1 if it was not found
//TODO implement
int BufSub(Buffer* buffer, char* string);

//Clears all of the info in the buffer - eg Zeroes it out
void BufClear(Buffer* buffer);

#endif