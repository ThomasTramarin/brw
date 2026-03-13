#include "terminal.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/* Original terminal state, restored on exit */
static struct termios orig_termios;

/* Restore terminal to original state */
void term_disable_conf() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

/* Enable raw mode (disable canonical and echo)*/
void term_enable_conf() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(term_disable_conf); // restore on exit
    struct termios new = orig_termios;
    new.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
}

bool term_get_size(u32 *w, u32 *h) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        *w = ws.ws_col;
        *h = ws.ws_row;
        return true;
    } else
        return false;
}