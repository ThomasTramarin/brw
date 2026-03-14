#include "editor.h"

void editor_init(editor_t *e, display_t *disp, term_t *term, file_ctx_t *fc) {
    e->disp = disp;
    e->term = term;
    e->fc = fc;
    e->file_offset = 0;
    e->running = false;
}

// main loop
void editor_run(editor_t *e) {
    e->running = true;

    display_render(e->disp);

    while (e->running) {
        int key = term_read_key();

        if (key == KEY_NONE) {
            continue;
        }

        // test
        display_put(e->disp, 0, 0, (cell_t){.c = key, .attr = CELL_A_DIM, .fg = CELL_C_WHITE});

        // exit
        if (key == 'q') {
            e->running = false;
        }

        // render
        display_render(e->disp);
    }
}