#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXTOKEN 1024
typedef enum {
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    PRIMITIVE = 4
} type_t;

typedef struct {
    type_t type;
    int start;
    int end;
    int stringLength;
    int size;


} tok_t;

typedef struct {
    tok_t tokens[MAXTOKEN];
}JSON;


char *readFile(char *filename, int *readSize);
void parser(char *text, int size, JSON *json, int* howmany);
void print(JSON *json);

//void free(JSON *json);