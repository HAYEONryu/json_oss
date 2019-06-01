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
	int posOfNameToken = 0;
	int i = 0;

	if (text[position] != '{')
	{
		return;
	} //check it is started properly

	while (position < size)
	{
		// NAME token
		if (text[position] == '"')
		{
			parser_nameToken(text, json, &position, &numberoftoken, &posOfNameToken);
		}

		// VALUE token
		if (text[position] == ':')
		{
			position++;
			parser_valueToken(text, json, &position, &numberoftoken, &posOfNameToken);
		}

		position++;
	}

	/*if (text[position] != '}')
	{
		return;


		while (position < size)
		{ // until end of value and line

		//value token
		numberoftoken++;
		position++;
		valrecur(text, json, size, &position, &numberoftoken);

		//name token size check
		if (text[position] == ',')
		{
		json->tokens[a].size++;
		position++;
		}
		//end
		if (text[position - 1] == ',' && text[position] == '\n') {
		break;
		}
		}
	}*/

	*howmanytokens = numberoftoken - 1;
}

///////////////////////////////////////////////////////////////////

void valrecur(char *text, JSON *json, int size, int *nth, int *numberoftoken) {
	//value token checker
	int pre=0;

	for (; text[*nth] == 32; (*nth)++) ;

	switch (text[*nth])
	{ // Start Switch
		//define type
	case '"':
	{
		json->tokens[*numberoftoken].type = STRING;
		json->tokens[*numberoftoken].start = ++(*nth);
		while (text[*nth] != '"')
			(*nth)++;
		json->tokens[*numberoftoken].end = *nth-1;
		json->tokens[*numberoftoken].size = 0;
		json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start;
		break;
	}

	case '{':
	{
		json->tokens[*numberoftoken].type = OBJECT;
		json->tokens[*numberoftoken].start = ++(*nth);
		
		int objTokenIdx = *numberoftoken;







		while (text[*nth] != '}') {
			if (text[*nth] == ',') {
				json->tokens[*numberoftoken].size++;
				pre = (*numberoftoken);
				(*numberoftoken)++;
				valrecur(text, json, size, nth, numberoftoken);
			}
			(*nth)++;
		}
		json->tokens[pre].end = *nth-1;
		json->tokens[pre].stringLength = json->tokens[pre].end - json->tokens[pre].start;
		break;
	}

	case '[':
	{
		json->tokens[*numberoftoken].type = ARRAY;
		json->tokens[*numberoftoken].start = ++(*nth);
		while (text[*nth] != ']') {
			if (text[*nth] == ',') {
				json->tokens[*numberoftoken].size++;
				pre = (*numberoftoken);
				(*numberoftoken)++;
				valrecur(text, json, size, nth, numberoftoken);
			}
			(*nth)++;
		}
		json->tokens[pre].end = *nth-1;
		json->tokens[pre].stringLength = json->tokens[pre].end - json->tokens[pre].start;
		break;
	}

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
		json->tokens[*numberoftoken].type = PRIMITIVE;
		json->tokens[*numberoftoken].start = ++(*nth);
		json->tokens[*numberoftoken].size = 0;
		while (text[*nth] != ' '&& text[*nth] != '\n')
			(*nth)++;
		json->tokens[*numberoftoken].end = *nth;
		json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start;
		break;
	}
	case '\n':
	case '\t':
	case ' ':
	{
		(*nth)++;
		valrecur(text, json, size, nth, numberoftoken);
		break;
	}
	/*
	default:
	{
		json->tokens[*numberoftoken].type = UNDEFINED;
		json->tokens[*numberoftoken].start = (*nth) + 1;
		json->tokens[*numberoftoken].size = 0;
		while (!(text[*nth - 1] == ',' && text[*nth] == '\n')) {
			(*nth)++;
		}
		json->tokens[*numberoftoken].end = *nth;
		json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start;

		break;
	}
	*/
	} // End Switch

	(*nth)++;
	(*numberoftoken)++;
}


void parser_nameToken(char* text, JSON* json, int* nth, int* numberoftoken, int* pos) {

	// name token
	json->tokens[*numberoftoken].type = STRING;
	json->tokens[*numberoftoken].start = ++(*nth);
	*pos = *numberoftoken;
	

	// find end of name token
	for (; text[(*nth)] != '"'; (*nth)++);

	json->tokens[*numberoftoken].end = (*nth) - 1;
	json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start + 1;
	json->tokens[*numberoftoken].value = malloc(sizeof(char) * json->tokens[*numberoftoken].stringLength + 1);

	memset(json->tokens[*numberoftoken].value, '\0', json->tokens[*numberoftoken].stringLength+1);
	memcpy(json->tokens[*numberoftoken].value, &(text[json->tokens[*numberoftoken].start]), json->tokens[*numberoftoken].stringLength);

	(*nth)++;
	(*numberoftoken)++;
}

void parser_valueToken(char* text, JSON* json, int* nth, int* numberoftoken, int* pos) {
	// erase white space
	for (; text[*nth] == 32; (*nth)++);

	switch (text[*nth])
	{ // Start Switch
	  //define type
	case '"':
		// STRING
		parser_valueToken_STRING(text, json, nth, numberoftoken);
		json->tokens[*pos].size++;
		break;
	case '{':
		// OBJECT
		parser_valueToken_OBJECT(text, json, nth, numberoftoken, pos);
		json->tokens[*pos].size++;
		break;
	case '[':
		// ARRAY
		//parser_valueToken_ARRAY(text, json, nth, numberoftoken, pos);
		json->tokens[*pos].size++;
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
		// PRIMITIVE
		parser_valueToken_PRIMITIVE(text, json, nth, numberoftoken);
		json->tokens[*pos].size++;
		break;

	} // End Switch

	//(*numberoftoken)++;
}

void parser_valueToken_STRING(char* text, JSON* json, int* nth, int* numberoftoken) {
	// name token
	json->tokens[*numberoftoken].type = STRING;
	json->tokens[*numberoftoken].start = ++(*nth);

	// find end of name token
	for (; text[(*nth)] != '"'; (*nth)++);

	json->tokens[*numberoftoken].end = (*nth) - 1;
	json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start + 1;
	json->tokens[*numberoftoken].value = malloc(sizeof(char) * json->tokens[*numberoftoken].stringLength + 1);

	memset(json->tokens[*numberoftoken].value, '\0', json->tokens[*numberoftoken].stringLength + 1);
	memcpy(json->tokens[*numberoftoken].value, &(text[json->tokens[*numberoftoken].start]), json->tokens[*numberoftoken].stringLength);

	(*nth)++;
	(*numberoftoken)++;
}

void parser_valueToken_OBJECT(char* text, JSON* json, int* nth, int* numberoftoken, int* pos) {
	int cnt = 0;

	json->tokens[*numberoftoken].type = OBJECT;
	json->tokens[*numberoftoken].start = ++(*nth);


	
	for (; text[(*nth)] != '}'; (*nth)++) {
		if (text[(*nth)] == '"')
		{
			parser_nameToken(text, json, nth, numberoftoken, pos);
		}

		// VALUE token
		if (text[(*nth)] == ':')
		{
			(*nth)++;
			parser_valueToken(text, json, nth, numberoftoken, pos);
		}
	}




	json->tokens[*numberoftoken].end = (*nth) - 1;
	json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start + 1;
	json->tokens[*numberoftoken].value = malloc(sizeof(char) * json->tokens[*numberoftoken].stringLength + 1);

	memset(json->tokens[*numberoftoken].value, '\0', json->tokens[*numberoftoken].stringLength + 1);
	memcpy(json->tokens[*numberoftoken].value, &(text[json->tokens[*numberoftoken].start]), json->tokens[*numberoftoken].stringLength);
	
	(*nth)++;
	(*numberoftoken)++;
}

void parser_valueToken_ARRAY(char* text, JSON* json, int* nth, int* numberoftoken, int* pos) {
	json->tokens[*numberoftoken].type = ARRAY;
	json->tokens[*numberoftoken].start = ++(*nth);



	(*nth)++;
	(*numberoftoken)++;
}

void parser_valueToken_PRIMITIVE(char* text, JSON* json, int* nth, int* numberoftoken) {
	json->tokens[*numberoftoken].type = PRIMITIVE;
	json->tokens[*numberoftoken].start = (*nth)++;

	for (; text[(*nth)] != ','; (*nth)++);

	json->tokens[*numberoftoken].end = (*nth) - 1;
	json->tokens[*numberoftoken].stringLength = json->tokens[*numberoftoken].end - json->tokens[*numberoftoken].start + 1;
	json->tokens[*numberoftoken].value = malloc(sizeof(char) * json->tokens[*numberoftoken].stringLength + 1);

	memset(json->tokens[*numberoftoken].value, '\0', json->tokens[*numberoftoken].stringLength + 1);
	memcpy(json->tokens[*numberoftoken].value, &(text[json->tokens[*numberoftoken].start]), json->tokens[*numberoftoken].stringLength);

	(*nth)++;
	(*numberoftoken)++;
}
