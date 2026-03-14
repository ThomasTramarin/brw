#ifndef TERMINAL_H
#define TERMINAL_H
#include "types.h"

typedef struct {
    u32 width;  // current width (rows) of the terminal
    u32 height; // current height (cols) of the terminal
} term_t;

bool term_init(term_t *t);

typedef enum {
    KEY_NONE = 0,
} term_key_t;

int term_read_key();

#endif