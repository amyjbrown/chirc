/*
*  chirc: a simple multi-threaded IRC server
* 
*  Message interface
*  This describes the format for creating a more structured message format froma  raw message
*/

#ifndef CHIRC_MESSAGE_H_
#define CHIRC_MESSAGE_H_

#include <stdbool.h>

/*
*  RawMessage
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
    char* final;
} RawMessage; 

typedef enum {
    MTNick,
    MTUser
} MsgType;

#define MSG_IS(msg, type) (msg.header == type)

typedef struct {
    MsgType type;
} Message;


typedef struct {
    Message header;
    char* user;
    char* mode;
    char* realname;
} UserMsg;


typedef struct {
    Message header;
    char* nick;
} NickMsg;

//Takes a string-buffer and parses it into resulting RawMessage out
//Returns bool to signify success or failure
//TODO: set it to ErrorEnum later
bool RawMsgLex(char* string, RawMessage* out);
RawMessage* RawMsgInit(RawMessage* rm);
bool MsgParse(RawMessage* rm, Message* out);

#endif