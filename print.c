#include "header.h"
void print(char *text, JSON *json, int howmany){
    for (int i = 0; i<= howmany; i++){
        printf("[%d] ", i+1);
        for(int j = json->tokens[i].start; j<= json->tokens[i].end; j++){
            printf("%c", text[j]);
        }
        printf("  (size=%d, %d~%d, ", json->tokens[i].size, json->tokens[i].start, json->tokens[i].end);
		switch (json->tokens[i].type)
		{
		case STRING:
			printf("JSNM_STRING)\n");
			break;
		case OBJECT:
			printf("JSNM_OBJECT)\n");
			break;
		case PRIMITIVE:
			printf("JSNM_PRIMITIVE)\n");
			break;
		case ARRAY:
			printf("JSNM_ARRAY)\n");
			break;
		case UNDEFINED:
			printf("JSNM_UNDEFINED)\n");
			break;
		default:
			printf("ERROR)\n");
			break;
		}
    }        
}
