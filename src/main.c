#include "display.h"
#include "editor.h"
#include "terminal.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    term_t t;
    if (!term_init(&t)) {
        fprintf(stderr, "error: term_init()\n");
        return 1;
    }

    display_t d;
    // set the terminal size as the display size
    if (!display_init(&d, t.width, t.height)) {
        fprintf(stderr, "error: display_init()\n");
        return 1;
    }

    editor_t e;
    editor_init(&e, &d, &t, NULL);

    // enter the main loop
    editor_run(&e);
    return 0;
}