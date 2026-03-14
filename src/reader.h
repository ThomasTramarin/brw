#ifndef READER_H
#define READER_H
#include "types.h"

typedef struct {
    char *filename;
    u8 *data;
    usize size; // the size of the file in bytes
} file_ctx_t;

bool reader_file_open(file_ctx_t *fc, const char *filename);
void reader_file_close(file_ctx_t *fc);

#endif