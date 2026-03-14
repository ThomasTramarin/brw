#ifndef EDITOR_H
#define EDITOR_H
#include "display.h"
#include "reader.h"
#include "terminal.h"
#include "types.h"

typedef struct {
    display_t *disp;
    term_t *term;
    file_ctx_t *fc;

    u64 file_offset; // Offset of the first rendered byte (top-left corner)
    bool running;
} editor_t;

void editor_init(editor_t *e, display_t *disp, term_t *term, file_ctx_t *fc);
void editor_run(editor_t *e);

#endif