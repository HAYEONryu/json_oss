#include "header.h"
#define TOKEN_COUNT 1024

void parser(char *text, int size, JSON *json, int *howmanytokens)
{

    int tokenIndex = 0;
    int position = 0;
    int countrange = 0;
    int numberoftoken = 0;
    int nametoken;
    int linetoken;
    int forsize = 0;
    int i = 0;

    {
        /* data */
    };

    if (text[position] == '{')
    {
        //json->tokens[0] is the most outter token
        json->tokens[numberoftoken].type = OBJECT;
        json->tokens[numberoftoken].start = position + 1;
        position++;
        numberoftoken++;
    }
    else
    {
        return;
    } //check it is started properly

    while (position < size)
    {
        if (text[position] == '"')
        {
            //line token
            json->tokens[numberoftoken].type = OBJECT;
            json->tokens[numberoftoken].start = position + 1;
            linetoken = numberoftoken;
            numberoftoken++;
            position++;

            // name token
            json->tokens[numberoftoken].type = STRING;
            json->tokens[numberoftoken].start = position + 1;
            numberoftoken++;
            position++;
            for (; text[position] = '"'; position++)
            {
            }
            if (text[position] = '"')
            {
                json->tokens[numberoftoken].end = position;
                json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start + 1;
            }
        }
        if (text[position] == ':')
        {
            while (position < size)
            { // until end of value and line

                //value token
                nametoken = numberoftoken;
                numberoftoken++;
                valrecur(text, &json, size, &position, &numberoftoken);

                //name token size check
                if (text[position] = ',')
                {
                    json->tokens[nametoken].size++;

                    //end of line
                    if (text[position - 1] == ',' && text[position] == '\n')
                    {
                        //the most outter token size check
                        json->tokens[0].size++;
                        json->tokens[linetoken].end = position;
                        json->tokens[linetoken].stringLength = json->tokens[linetoken].end - json->tokens[linetoken].start + 1;
                        json->tokens[linetoken].size = json->tokens[nametoken].size + 1;
                        break;
                    }
                }

                position++;
            }
        }
        if (text[position] = '}')
        {
            json->tokens[0].end = position;
            json->tokens[0].stringLength = json->tokens[0].end - json->tokens[0].start + 1;
        }
        position++;
    }

    ///////////////////////////////////////////////////////////////////

    void valrecur(char *text, JSON *json, int size, int *nth, int *numberoftoken)
    {
        int nthtoken = *numberoftoken;
        int position = *nth;

    //value token checker
while (position < size)
            {
                switch (text[position])
                { //define type
                case '"':
                {
                    json->tokens[nthtoken].type = STRING;
                    json->tokens[nthtoken].start = position + 1; //where to start after "
                    while (text[position] != '"')
                        position++;
                    json->tokens[nthtoken].end = position;
                    json->tokens[nthtoken].stringLength = json->tokens[nthtoken].end - json->tokens[nthtoken].start;
                }
                break;

                case '{':
                {
                    json->tokens[nthtoken].type = OBJECT;

                    position++;
                    json->tokens[nthtoken].start = position + 1; //where to start after "

                    json->tokens[nthtoken].stringLength = json->tokens[nthtoken].end - json->tokens[numberoftoken].start;
                    while (text[position] != '}')
                        position++;
                    json->tokens[nthtoken].end = position;
                    json->tokens[nthtoken].stringLength = json->tokens[nthtoken].end - json->tokens[nthtoken].start;
                }
                break;

                case '[':
                {
                    json->tokens[numberoftoken].type = ARRAY;
                    json->tokens[numberoftoken].start = position + 1; //where to start after "
                    while (text[position] != ']')
                        position++;
                    json->tokens[numberoftoken].end = position;

                    json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
                }
                break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '-':
                {
                    json->tokens[numberoftoken].type = PRIMITIVE;
                    json->tokens[numberoftoken].start = position; //where to start after "
                    while (text[position] != ' ')
                        position++;
                    json->tokens[numberoftoken].end = position;

                    json->tokens[numberoftoken].stringLength = json->tokens[numberoftoken].end - json->tokens[numberoftoken].start;
                }
                break;
                }
                i = position;
                if (text[i] == ':')
                {
                    i = i + 1;
                    while (text[i] != ':')
                    {
                        if (text[i] == ',')
                            forsize++;
                        i++;
                    }
                }

                json->tokens[numberoftoken].size = forsize;
                forsize = 0;
                numberoftoken++;
            }
        numberoftoken--;
        howmanytokens = &numberoftoken;
    }
            
}