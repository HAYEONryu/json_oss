#include "header.h"

//#include <json/json.h>
//#include "parson.h"

void main() {
    
    int size;

    char *text = readFile("", &size);

    /*for(int i = 0; i < size; i++) {
        json->buffer[i];
    }*/
    
    JSON json = {0, };
    parse(text, size, &json);
    
    return 0;
}