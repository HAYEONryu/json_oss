#include "header.h"

//#include <json/json.h>
//#include "parson.h"

int main() {
    
    int* size;

    char* text ;
    int howmany;
    text = readFile("menu.json", size );

    //size1 = text.length();
    
    JSON json = {0, };
    howmany = parser(text, &size, &json);
    print(text, &json, howmany);
    return 0;
}