#include "header.h"

//#include <json/json.h>
//#include "parson.h"

int main() {
    
    int size;

    //char *text = readFile("", &size);

    /*for(int i = 0; i < size; i++) {
        json->buffer[i];
    }*/
    char text = " {
    "Espresso":
    {
        "Cappucino" : "5.0",
        "Cafe latte" : "4.2",
        "Americano" : "3.5",
        "Mocha" : "3.0",
        "Macchiato" : "5.0",
        "Hot chocolate" : "3.0"
    }, }";
    size = text.length();
    
    JSON json = {0, };
    parser(text, size, &json);
    
    return 0;
}