#include "header.h"
#define TOKEN_COUNT 1024

void parser(char *text, int size, JSON *json) {

    int tokenIndex = 0;
    int position = 0; 
    int countrange = 0;
    int numberoftoken = 0;
    {
        /* data */
    };
    
    if(text[position] != '{') { //check it is started properly 
        return;
    }

    while(position < size) { 
        switch (text[position]) { //define type
            case '"':
            {   json->tokens[numberoftoken].type = STRING;
                json->tokens[numberoftoken].start = position + 1; //where to start after "
                while (text[position] != '"' )
                    position++;    
                json->tokens[numberoftoken].end = position;

                if (json->tokens[numberoftoken].end == NULL) //if no " closed, wrong, break the loop 
                    break;

                int stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
/*
                json->tokens[tokenIndex].type = STRING;
                json->tokens[tokenIndex].string = malloc(stringLength + 1);
                memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

                memcpy(json->tokens[tokenIndex].string, start, stringLength);

                tokenIndex++;

                position = position + stringLength + 1;
                */
            }
            break;

            case '{':
            {
                json->tokens[numberoftoken].type = OBJECT;
                /*json->tokens[tokenIndex].string = malloc(stringLength + 1);
                memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
                memcpy(json->tokens[tokenIndex].string, start, stringLength);*/
                position++;
               json->tokens[numberoftoken].start = position + 1; //where to start after "

                int stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
                while(text[position] != '}')
                    position++;    
                json->tokens[numberoftoken].end = position;
                if (json->tokens[numberoftoken].end == NULL) //if no " closed, wrong, break the loop 
                    break;
                        /*
                        json->tokens[tokenIndex].type = STRING;
                        json->tokens[tokenIndex].string = malloc(stringLength + 1);
                        memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
                        memcpy(json->tokens[tokenIndex].string, start, stringLength);
                        tokenIndex++;

                        position = position + stringLength + 1;
                    }
                    position++;
      
                }
                              */
            }
            break;

            case '[':
            {
                json->tokens[numberoftoken].type = ARRAY;
                json->tokens[numberoftoken].start = position + 1; //where to start after "
                while(text[position] != ']')
                    position++;    
                json->tokens[numberoftoken].end = position;

                if (json->tokens[numberoftoken].end == NULL) //if no " closed, wrong, break the loop 
                    break;

                int stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
/*

                        json->tokens[tokenIndex].type = STRING;
                        json->tokens[tokenIndex].string = malloc(stringLength + 1);
                        json->tokens[tokenIndex].isArray = true;
                        memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
                        memcpy(json->tokens[tokenIndex].string, start, stringLength);
                        tokenIndex++;

                        position = position + stringLength + 1;
                    }
                    position++;
                }*/
            }
            break;

            case '0': case '1': case '2': case '3': case '4': case '5': case '6':
            case '7': case '8': case '9': case '-':
            {
                json->tokens[numberoftoken].type = PRIMITIVE;
                json->tokens[numberoftoken].start = position ; //where to start after "
                while(text[position] != ' ')
                    position++;    
                json->tokens[numberoftoken].end = position;

                if (json->tokens[numberoftoken].end == NULL) //if no " closed, wrong, break the loop 
                    break;

                int stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
/*
                char *buffer;

                buffer = malloc(stringLenth + 1);
                memset(buffer, 0, stringLenth + 1);

                json->tokens[tokenIndex].number = atof(buffer);
                free(buffer);
                tokenIndex++;
                position = position + stringLenth + 1; */
            }
            break;
        }
        numberoftoken++;

    }
}

void free(JSON *json) {
    for(int i = 0; i < TOKEN_COUNT; i++) {
        if (json->tokens[i].type == STRING)
            free(json->tokens[i].string);
    }
}
