#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXTOKEN 1024

typedef enum {
	UNDEFINED = 0,
	OBJECT = 1,
	ARRAY = 2,
	STRING = 3,
	PRIMITIVE = 4
} type_t;

typedef struct {
	type_t type;
	char* value;
	int start;
	int end;
	int stringLength;
	int size;
	int parent;
} tok_t;

typedef struct {
	tok_t tokens[MAXTOKEN];
}JSON;


char *readFile(char *filename, int *readSize);
void parser(char* text, int size, JSON *json, int* howmanytokens);
void print(char* text, JSON *json, int i);

void parser_nameToken(char* text, JSON* json, int* pIdx, int* pNoT, int* pos);
void parser_valueToken(char* text, JSON* json, int* pIdx, int* pNoT);
void parser_valueToken_STRING(char* text, JSON* json, int* pIdx, int* pNoT);
void parser_valueToken_OBJECT(char* text, JSON* json, int* pIdx, int* pNoT);
void parser_valueToken_ARRAY(char* text, JSON* json, int* pIdx, int* pNoT);
void parser_valueToken_PRIMITIVE(char* text, JSON* json, int* pIdx, int* pNoT);
void parser_valueToken_STRING_integrated(char* text, JSON* json, int* pIdx, int* pNoT, int* parentPos);
