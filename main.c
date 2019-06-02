#include "header.h"

int main(int argc, char *argv[]) {

	int size;

	char *text;
	int howmany = 0;
	printf("1\n");
	text = readFile(argv[1], &size);
	//char* readFile(argv[1], &size);
	printf("2\n");

	JSON json = { 0, };
	parser(text, size, &json, &howmany);
	printf("3\n");
	print(text, &json, howmany);
	printf("4\n");
	return 0;
}


