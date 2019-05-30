#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *readFile(char *filename, int *readSize) { //read file

    FILE *fp = fopen(filename, "r+");

    if (fp == NULL) {
    return NULL;
    }

    int size;
    

    //size of file
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char *buffer[size];
    
    //buffer = (char*)malloc(sizeof(char)*size);
    //buffer = (char*)malloc(size + 1);
    memset(buffer, 0, size + 1);

    //fread(buffer, 1, size, fp)
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