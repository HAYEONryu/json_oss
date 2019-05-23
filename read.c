#include "header.h"

char *readFile(char *filename, int *readSize) { //read file

    FILE *fp = fopen(filename, "file");

    if (fp == NULL) {
    return NULL;
    }

    int size;
    char *buffer;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);

    if (fread(buffer, size, 1, fp) < 1) {
    *readSize = 0;
    free(buffer);
    fclose(fp);
    return NULL;
    }

    *readSize = size;

    fclose(fp);

    return buffer;

}