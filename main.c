#include "header.h"

//#include <json/json.h>
//#include "parson.h"

int main(int argc, char** argv) {
    
    int size;

    //char *text ;
    int howmany;
    char* text = readFile(argv[1], &size );
    //char* readFile(argv[1], &size);
    
    JSON json = {0, };
    parser(text, size, &json, &howmany);
    print(text, &json, howmany);
    return 0;
}