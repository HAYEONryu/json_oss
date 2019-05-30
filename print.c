#include "header.h"
void print(char *text, JSON *json, int* howmany){
    int howmanytokens = howmany;
    for (int i = 0; i<= howmanytokens; i++){
        printf("[%d] ", i+1);
        for(int j = json->tokens[i].start; j<= json->tokens[i].end; j++)){
            printf("%c", text[j]);
        }
        printf(" (size=%d, %d~%d, %s) \n", json->tokens[i].size, json->tokens[i].start, json->tokens[i].end, json->tokens[i].type);
    }        
}