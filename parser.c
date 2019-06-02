#include "header.h"

#define TOKEN_COUNT 1024

void parser(char *text, int size, JSON *json, int *howmanytokens)
{
	int idx = 0;
	int numberOfToken = 0;

	if (text[idx] != '{') {
		fprintf(stderr, "Can't read json start obj\n");
		return;
	}
	idx++;


	while (idx < size) {
		// remove space
		for (; text[idx] == 32; idx++);

		int parentPos = -1;

		// name
		if (text[idx] == '"') {
			//parser_valueToken_STRING_integrated(text, json, &idx, &numberOfToken, &parentPos);
			parser_nameToken(text, json, &idx, &numberOfToken, &parentPos);
		}

		// value
		if (text[idx] == ':') {
			idx++;
			parser_valueToken(text, json, &idx, &numberOfToken);
		}

		idx++;
	}

	*howmanytokens = numberOfToken-1;
}

void parser_nameToken(char* text, JSON* json, int* pIdx, int* pNoT, int* parentPos) {
	// name token
	json->tokens[*pNoT].type = STRING;
	json->tokens[*pNoT].start = ++(*pIdx);
	if(*parentPos > 0)
		json->tokens[*parentPos].size++;
	json->tokens[*pNoT].size = 1;

	// find end of name token
	for (; text[(*pIdx)] != '"' || (text[(*pIdx)] == '"' && text[(*pIdx) - 1] == '\\'); (*pIdx)++);

	json->tokens[*pNoT].end = (*pIdx);
	json->tokens[*pNoT].stringLength = json->tokens[*pNoT].end - json->tokens[*pNoT].start;

	json->tokens[*pNoT].value = malloc(sizeof(char) * (json->tokens[*pNoT].stringLength + 1));
	memset(json->tokens[*pNoT].value, '\0', json->tokens[*pNoT].stringLength + 1);
	memcpy(json->tokens[*pNoT].value, &(text[json->tokens[*pNoT].start]), json->tokens[*pNoT].stringLength);

	(*pIdx)++;
	(*pNoT)++;
}

void parser_valueToken(char* text, JSON* json, int* pIdx, int* pNoT) {
	// remove space
	for (; text[*pIdx] == 32 || text[*pIdx] == 10; (*pIdx)++);

	switch (text[*pIdx])
	{ // Start Switch
	  //define type
	case '"':
		// STRING
		parser_valueToken_STRING(text, json, pIdx, pNoT);
		break;
	case '{':
		// OBJECT
		parser_valueToken_OBJECT(text, json, pIdx, pNoT);
		break;
	case '[':
		// ARRAY
		parser_valueToken_ARRAY(text, json, pIdx, pNoT);
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
	case 't':
	case 'f':
	case 'n':
		// PRIMITIVE
		parser_valueToken_PRIMITIVE(text, json, pIdx, pNoT);
		break;

	} // End Switch

	  //(*numberoftoken)++;
}

void parser_valueToken_STRING(char* text, JSON* json, int* pIdx, int* pNoT) {
	// name token
	json->tokens[*pNoT].type = STRING;
	json->tokens[*pNoT].start = ++(*pIdx);
	json->tokens[*pNoT].size = 0;

	// find end of string token
	for (; text[(*pIdx)] != '"' || (text[(*pIdx)] == '"' && text[(*pIdx)-1] == '\\'); (*pIdx)++);

	json->tokens[*pNoT].end = (*pIdx);
	json->tokens[*pNoT].stringLength = json->tokens[*pNoT].end - json->tokens[*pNoT].start;

	json->tokens[*pNoT].value = malloc(sizeof(char) * (json->tokens[*pNoT].stringLength + 1));
	memset(json->tokens[*pNoT].value, '\0', json->tokens[*pNoT].stringLength + 1);
	memcpy(json->tokens[*pNoT].value, &(text[json->tokens[*pNoT].start]), json->tokens[*pNoT].stringLength);

	(*pIdx)++;
	(*pNoT)++;
}

void parser_valueToken_STRING_integrated(char* text, JSON* json, int* pIdx, int* pNoT, int* parentPos) {
	// name token
	json->tokens[*pNoT].type = STRING;
	json->tokens[*pNoT].start = ++(*pIdx);
	if (*parentPos > 0)
		json->tokens[*parentPos].size++;


	// find end of string token
	for (; text[(*pIdx)] != '"' || (text[(*pIdx)] == '"' && text[(*pIdx) - 1] == '\\'); (*pIdx)++);

	json->tokens[*pNoT].end = (*pIdx);
	json->tokens[*pNoT].stringLength = json->tokens[*pNoT].end - json->tokens[*pNoT].start;

	json->tokens[*pNoT].value = malloc(sizeof(char) * (json->tokens[*pNoT].stringLength + 1));
	memset(json->tokens[*pNoT].value, '\0', json->tokens[*pNoT].stringLength + 1);
	memcpy(json->tokens[*pNoT].value, &(text[json->tokens[*pNoT].start]), json->tokens[*pNoT].stringLength);

	(*pIdx)++;
	(*pNoT)++;
}


void parser_valueToken_OBJECT(char* text, JSON* json, int* pIdx, int* pNoT) {
	json->tokens[*pNoT].type = OBJECT;
	json->tokens[*pNoT].start = (*pIdx);

	// find end of obj
	int tempIdx = *pIdx + 1;
	int cnt = 0;
	int parentPos = 0;

	while (true) {
		if (cnt == 0 && text[tempIdx] == '}') {
			break;
		}
		if (cnt > 0 && text[tempIdx] == '}') {
			cnt--;
		}
		if (text[tempIdx] == '{') {
			cnt++;
		}
		tempIdx++;
	}
	
	json->tokens[*pNoT].end = tempIdx+1;
	json->tokens[*pNoT].stringLength = json->tokens[*pNoT].end - json->tokens[*pNoT].start;

	json->tokens[*pNoT].value = malloc(sizeof(char) * (json->tokens[*pNoT].stringLength + 1));
	memset(json->tokens[*pNoT].value, '\0', json->tokens[*pNoT].stringLength + 1);
	memcpy(json->tokens[*pNoT].value, &(text[json->tokens[*pNoT].start]), json->tokens[*pNoT].stringLength);

	parentPos = (*pNoT)++;
	// traverse inside of obj
	while (*pIdx < tempIdx) {
		// remove space
		for (; text[*pIdx] == 32; (*pIdx)++);

		// name
		if (text[*pIdx] == '"') {
			parser_nameToken(text, json, pIdx, pNoT, &parentPos);
		}

		// value
		if (text[*pIdx] == ':') {
			(*pIdx)++;
			parser_valueToken(text, json, pIdx, pNoT);
		}

		(*pIdx)++;
	}

	// End of traverse

	*pIdx = tempIdx;
	
	(*pIdx)++;
}

void parser_valueToken_ARRAY(char* text, JSON* json, int* pIdx, int* pNoT) {
	json->tokens[*pNoT].type = ARRAY;
	json->tokens[*pNoT].start = (*pIdx);

	// find end of obj
	int tempIdx = *pIdx + 1;
	int aCnt = 0;
	int oCnt = 0;
	int cntComma = 0;
	int parentPos = 0;

	while (true) {
		if (aCnt == 0 && text[tempIdx] == ']') {
			break;
		}
		if (aCnt > 0 && text[tempIdx] == ']') {
			aCnt--;
		}
		if (oCnt > 0 && text[tempIdx] == '}') {
			oCnt--;
		}
		if (text[tempIdx] == '[') {
			aCnt++;
		}
		if (text[tempIdx] == '{') {
			oCnt++;
		}
		if (text[tempIdx] == ',' && aCnt == 0 && oCnt == 0) {
			cntComma++;
		}
		tempIdx++;
	}

	json->tokens[*pNoT].size = cntComma+1;
	json->tokens[*pNoT].end = tempIdx+1;
	json->tokens[*pNoT].stringLength = json->tokens[*pNoT].end - json->tokens[*pNoT].start;

	json->tokens[*pNoT].value = malloc(sizeof(char) * (json->tokens[*pNoT].stringLength + 1));
	memset(json->tokens[*pNoT].value, '\0', json->tokens[*pNoT].stringLength + 1);
	memcpy(json->tokens[*pNoT].value, &(text[json->tokens[*pNoT].start]), json->tokens[*pNoT].stringLength);

	parentPos = (*pNoT)++;
	// traverse inside of obj
	(*pIdx)++;
	while (*pIdx < tempIdx) {

		// remove space
		for (; text[*pIdx] == 32 || text[*pIdx] == 10 || text[*pIdx] == ','; (*pIdx)++);

		parser_valueToken(text, json, pIdx, pNoT);
	}

	// End of traverse

	*pIdx = tempIdx;

	(*pIdx)++;
}

void parser_valueToken_PRIMITIVE(char* text, JSON* json, int* pIdx, int* pNoT) {
	json->tokens[*pNoT].type = PRIMITIVE;
	json->tokens[*pNoT].start = (*pIdx)++;

	while (true) {
		if (text[(*pIdx)] == ',')
			break;
		if (text[(*pIdx)] == '\n')
			break;
		(*pIdx)++;
	}

	json->tokens[*pNoT].end = (*pIdx);
	json->tokens[*pNoT].stringLength = json->tokens[*pNoT].end - json->tokens[*pNoT].start;

	json->tokens[*pNoT].value = malloc(sizeof(char) * (json->tokens[*pNoT].stringLength + 1));
	memset(json->tokens[*pNoT].value, '\0', json->tokens[*pNoT].stringLength + 1);
	memcpy(json->tokens[*pNoT].value, &(text[json->tokens[*pNoT].start]), json->tokens[*pNoT].stringLength);

	(*pIdx)++;
	(*pNoT)++;
}
