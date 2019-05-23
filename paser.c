#include "header.h"
#define TOKEN_COUNT 1024

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

                json->tokens[tokenIndex].type = STRING;
                json->tokens[tokenIndex].string = malloc(stringLength + 1);
                memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

                memcpy(json->tokens[tokenIndex].string, start, stringLength);

                tokenIndex++;

                position = position + stringLength + 1;
            }
            break;

            case '{':
            {
                json->tokens[tokenIndex].type = OBJECT;
                /*json->tokens[tokenIndex].string = malloc(stringLength + 1);
                memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
                memcpy(json->tokens[tokenIndex].string, start, stringLength);*/
                position++;

                while(text[position] != '}')
                {
                    if(text[position] == '"') {
                        char *start = text + position + 1;
                        char *end = strchr(start, '"');
                        if(end == NULL)
                            break;
                        int stringLength = end - start;
                        
                        json->tokens[tokenIndex].type = STRING;
                        json->tokens[tokenIndex].string = malloc(stringLength + 1);
                        memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
                        memcpy(json->tokens[tokenIndex].string, start, stringLength);
                        tokenIndex++;

                        position = position + stringLength + 1;
                    }
                    position++;
                }
            }

            case '[':
            {
                json->tokens[tokenIndex].type = ARRAY;
                /*json->tokens[tokenIndex].string = malloc(stringLength + 1);
                memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
                memcpy(json->tokens[tokenIndex].string, start, stringLength);*/
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

                        json->tokens[tokenIndex].type = STRING;
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
                buffer = malloc(stringLenth + 1);
                memset(buffer, 0, stringLenth + 1);

                json->tokens[tokenIndex].type = PRIMITIVE;
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
        if (json->tokens[i].type == STRING)
            free(json->tokens[i].string);
    }
}
