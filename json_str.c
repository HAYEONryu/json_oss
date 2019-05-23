#include <stdio.h>
#define TOKEN_COUNT 1024

//token structure
typedef struct {
    type_t type;
    int start;
    int end;
    int size;
} tok_t;

typedef enum {
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    PRIMITIVE = 4
} type_t;

typedef sturct {
    tok_t tokens[TOKEN_COUNT];
}JSON;