#include "header.h"

//#include <json/json.h>
//#include "parson.h"

int main() {
    
    int size;

    char* text ;
    int howmany;
    text = readFile("menu.json", &size );
    
    JSON json = {0, };
    parser(text, size, &json, &howmany);
    print(text, &json, howmany);
    return 0;
}