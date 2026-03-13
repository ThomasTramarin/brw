#include "display.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool display_init(display_t *d, u32 w, u32 h) {
    d->width = w;
    d->height = h;

    u32 n_cells = w * h;
    size_t size = (size_t)n_cells * sizeof(cell_t);

    d->buffer = malloc(size);
    d->backbuffer = malloc(size);

    if (!d->buffer || !d->backbuffer) {
        free(d->buffer);
        free(d->backbuffer);
        return false;
    }

    d->cursor_x = 0;
    d->cursor_y = 0;

    // initialize the display with empty cells
    for (u32 i = 0; i < n_cells; i++) {
        d->buffer[i] = CELL_EMPTY;
    }

    /**
     * Fill the backbuffer with bytes set to 0.
     * This will trigger renderization of all the cells at the first time.
     */
    memset(d->backbuffer, 0, size);

    return true;
}

void display_put(display_t *d, u32 x, u32 y, cell_t cell) {
    if (x < d->width && y < d->height) {
        d->buffer[y * d->width + x] = cell;
    }
}

void display_render(display_t *d) {
    for (u32 y = 0; y < d->height; y++) {
        for (u32 x = 0; x < d->width; x++) {
            u32 idx = y * d->width + x;
            if (memcmp(&d->buffer[idx], &d->backbuffer[idx], sizeof(cell_t)) != 0) {
                // move the cursor
                printf("\033[%d;%dH", y + 1, x + 1);

                // set attributes
                printf("\033[0m"); // reset
                if (d->buffer[idx].attr & CELL_A_BOLD)
                    printf("\033[1m");
                if (d->buffer[idx].attr & CELL_A_DIM)
                    printf("\033[2m");

                // set colors
                printf("\033[%dm", 30 + d->buffer[idx].fg);
                printf("\033[%dm", 40 + d->buffer[idx].bg);

                putchar(d->buffer[idx].c);

                d->backbuffer[idx] = d->buffer[idx];
            }
        }
    }
    printf("\033[%u;%uH", d->cursor_y + 1, d->cursor_x + 1);
    fflush(stdout);
}

void display_free(display_t *d) {
    free(d->buffer);
    free(d->backbuffer);
}