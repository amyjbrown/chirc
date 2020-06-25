/**
 * common.h
 * Common elements used by all interfaces
 * Macros:
 *  true, false: standard booleans
 * Types:
 *  enum chierror_t: Enum representing standard errors
*/
#ifndef CHI_COMMON_H_
#define CHI_COMMON_H_

#include <stdbool.h>

typedef enum {
    CEUnknown = false,  // Generic unknown error, 0 for compatibility with bool
    CEOk = true,        // OK Result code, true for compatbility with bool
    CESocketClosed,     // Socket being worked with has closed
    CEBufferError       // Arguement buffer is illdefined
} chierror_t;

#endif