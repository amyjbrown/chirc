/*
*  chirc: a simple multi-threaded IRC server
* 
*  Message interface
*  This describes the format for creating a more structured message format froma  raw message
*/

#ifndef CHIRCH_MESSAGE_H
/*
*  Message
*   
*  Structured format for looking at a message 
*  
*  Fields:
*   length (int):    length of message, including final 2 chars "\r\n"
*   prefix (char*):  pointer to the start of the prefix character
*   command (char*): pointer to start of the command substring
*   paramc (int):    length of paramters, from 0 (no parameters) to 15 (all parameters)
*   paramv (char**)  array of pointers to parameters  
*/
typedef struct {
    int length;
    char* prefix;
    char* command;
    int paramc;
    char** paramv;
} Message;

#endif