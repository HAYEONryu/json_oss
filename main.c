#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <json/json.h>
//#include "parson.h"

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

void parse(char *text, int size, JSON *json) {

    int tokenIndex = 0;
    int position = 0;

    if(text[position] != '{') {
        return;
    }

    position++;

    while(position < size) {
        switch (text[position]) {
            case '"':
            {
                char *start = text + position + 1;
                char *end = strchr(start, '"');
                if (end == NULL)
                    break;

                int stringLength = end - start;

                json->tokens[tokenIndex].type = TOKEN_STRING;
                json->tokens[tokenIndex].string = malloc(stringLength + 1);
                memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

                memcpy(json->tokens[tokenIndex].string, start, stringLength);

                tokenIndex++;

                position = position + stringLength + 1;
            }
            break;

            case '[':
            {
                position++;

                while(text[position] != ']')
                {
                    if(text[position] == '"') {
                        char *start = text + position + 1;
                        char *end = strchr(start, '"');
                        if(end == NULL) {
                            break;
                        }
                        int stringLength = end - start;

                        json->tokens[tokenIndex].type = TOKEN_STRING;
                        json->tokens[tokenIndex].string = malloc(stringLength + 1);
                        json->tokens[tokenIndex].isArray = true;
                        memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

                        memcpy(json->tokens[tokenIndex].string, start, stringLength);
                        tokenIndex++;

                        position = position + stringLength + 1;
                    }
                    position++;
                }
            }
            break;

            case '0': case '1': case '2': case '3': case '4': case '5': case '6':
            case '7': case '8': case '9': case '-':
            {
                char *start = text + position;
                char *end;
                char *buffer;

                end = strchr(text + position, ',');
                if(end == NULL) {
                    end = strchr(text + position, '}');
                    if(end == NULL)
                        break;
                }
                int stringLenth = end - start;
                bugger = malloc(stringLenth + 1);
                memset(buffer, 0, stringLenth + 1);

                json->tokens[tokenIndex].number = atof(buffer);
                free(buffer);
                tokenIndex++;
                position = position + stringLenth + 1;
            }
            break;
        }
        position++;
    }
}

void free(JSON *json) {
    for(int i = 0; i < TOKEN_COUNT; i++) {
        if (json->tokens[i].type == TOKEN_STRING)
            free(json->tokens[i].string);
    }
}


int main() {
    
    int size;

    char *text = readFile("", &size);

    /*for(int i = 0; i < size; i++) {
        json->buffer[i];
    }*/
    
    JSON json = {0, };
    parse(text, size, &json);
    

}