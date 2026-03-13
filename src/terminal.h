#ifndef TERMINAL_H
#define TERMINAL_H
#include "types.h"

void term_disable_conf();
void term_enable_conf();
bool term_get_size(u32 *w, u32 *h);

#endif