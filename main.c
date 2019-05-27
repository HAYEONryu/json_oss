#include "header.h"

//#include <json/json.h>
//#include "parson.h"

int main() {
    
    int* size;
    int size1 = 0;

    //char *text = readFile("", &size);

    /*for(int i = 0; i < size; i++) {
        json->buffer[i];
    }*/
    char* text ;
    text = readFile("munu.json", &size );

    //size1 = text.length();
    
    JSON json = {0, };
    parser(text, size, &json);
    
    return 0;
}