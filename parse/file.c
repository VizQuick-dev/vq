#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek failed");
        fclose(file);
        return NULL;
    }

    long filesize = ftell(file);
    if (filesize < 0) {
        perror("ftell failed");
        fclose(file);
        return NULL;
    }

    rewind(file);

    char *buffer = (char*)malloc(filesize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, filesize, file);
    if (read_size != filesize) {
        perror("fread failed");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[filesize] = '\0';

    fclose(file);
    return buffer;
}