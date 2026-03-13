#ifndef RENDER_H
#define RENDER_H
#include "types.h"

/* Colors */
#define CELL_C_BLACK 0
#define CELL_C_RED 1
#define CELL_C_GREEN 2
#define CELL_C_YELLOW 3
#define CELL_C_BLUE 4
#define CELL_C_MAGENTA 5
#define CELL_C_CYAN 6
#define CELL_C_WHITE 7

/* Attributes */
#define CELL_A_RESET (1 << 0)
#define CELL_A_BOLD (1 << 1)
#define CELL_A_DIM (1 << 2)

/* Struct to represent a character inside the terminal*/
typedef struct {
    u8 c;      // the char in ASCII
    u8 fg : 4; // foreground color, 4 bits
    u8 bg : 4; // background color, 4 bits
    u16 attr;  // bit mask with cell's attributes
} cell_t;

#define CELL_EMPTY ((cell_t){ \
    .c = ' ',                 \
    .fg = CELL_C_WHITE,       \
    .bg = CELL_C_BLACK,       \
    .attr = 0,                \
})

typedef struct {
    u32 width;  // current width (rows) of the terminal
    u32 height; // cirrent height (cols) of the terminal

    // cursor position inside the terminal
    u32 cursor_x;
    u32 cursor_y;

    cell_t *buffer;     // current screen buffer of cells
    cell_t *backbuffer; // previous buffer
} display_t;

bool display_init(display_t *d, u32 w, u32 h);
void display_free(display_t *d);

void display_put(display_t *d, u32 x, u32 y, cell_t cell);
void display_render(display_t *d);

#endif