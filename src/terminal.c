#include "terminal.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/* Original terminal state, restored on exit */
static struct termios orig_termios;

/* Restore terminal to original state */
static void term_disable_conf() {
    fflush(stdout);

    // exit the alternative screen
    printf("\x1b[?1049l");

    // show the cursor
    printf("\x1b[?25h");
    fflush(stdout);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void term_enable_conf() {
    struct termios new = orig_termios;
    new.c_lflag &= ~(ECHO | ICANON | ISIG);

    new.c_cc[VMIN] = 0;
    new.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);

    // enter the alternative screen
    printf("\033[?1049h");

    // hide the cursor
    printf("\033[?25l");
    fflush(stdout);
}

bool term_init(term_t *t) {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        return false;

    atexit(term_disable_conf);

    // set size
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        t->width = ws.ws_col;
        t->height = ws.ws_row;
    } else
        return false;

    term_enable_conf();
    return true;
}

int term_read_key() {
    u8 c;
    int nread;

    // read a character
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1)
            return -1;
        if (nread == 0)
            return KEY_NONE; // if no input in 0.1s
    }

    return (int)c;
}