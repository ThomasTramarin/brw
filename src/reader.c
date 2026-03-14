#include "reader.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

static char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *new = malloc(len);
    if (new) {
        memcpy(new, s, len);
    }
    return new;
}

bool reader_file_open(file_ctx_t *fc, const char *filename) {
    int fd = open(filename, O_RDONLY); // open the file in read-only mode
    if (fd < 0) {
        return false;
    }

    // get the size of the file
    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return false;
    }

    fc->size = (usize)st.st_size;

    if (fc->size == 0) {
        fc->data = NULL;
        close(fd);
        fc->filename = my_strdup(filename);
        return true;
    }

    // map the file
    fc->data = mmap(NULL, fc->size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (fc->data == MAP_FAILED) {
        close(fd);
        return false;
    }

    close(fd);
    fc->filename = my_strdup(filename);

    return (fc->filename != NULL);
}

void reader_file_close(file_ctx_t *fc) {
    if (fc->data && fc->data != MAP_FAILED) {
        munmap(fc->data, fc->size);
    }
    if (fc->filename) {
        free(fc->filename);
        fc->filename = NULL;
    }
}