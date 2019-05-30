#include "header.h"
#define TOKEN_COUNT 1024

void parser(char *text, int size, JSON *json, int *howmanytoken) {

    int tokenIndex = 0;
    int position = 0; 
    int countrange = 0;
    int numberoftoken = 0;
    int forsize = 0;
    int i = 0;

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
                while (text[position] != '"')
                    position++;    
                json->tokens[numberoftoken].end = position;
                json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;

            }
            break;

            case '{':
            {
                json->tokens[numberoftoken].type = OBJECT;

                position++;
               json->tokens[numberoftoken].start = position + 1; //where to start after "

                json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
                while(text[position] != '}')
                    position++;    
                json->tokens[numberoftoken].end = position;
                       
            }
            break;

            case '[':
            {
                json->tokens[numberoftoken].type = ARRAY;
                json->tokens[numberoftoken].start = position + 1; //where to start after "
                while(text[position] != ']')
                    position++;    
                json->tokens[numberoftoken].end = position;

                json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;

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

                json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;

            }
            break;
        }
        i = position;
        if(  text[i] == ':'){
            i = i+1;
            while ( text[i] != ':'){
                if(text[i] == ',')
                    forsize++;
                i++;

            }
        }

        json->tokens[numberoftoken].size = forsize;
        forsize = 0;
        numberoftoken++;
        
    }
    howmanytoken = numberoftoken-1;
}
