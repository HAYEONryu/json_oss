run : readFile.o parser.o main.o
	gcc -o run readFile.o parser.o main.o
readFile.o : readFile.c
	gcc -c -o readFile.o readFile.c
parser.o : parser.c
	gcc -c -o parser.o parser.c
main.o : main.c
	gcc -c -o main.o main.c