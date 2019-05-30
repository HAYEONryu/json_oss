run: readFile.o parser.o main.o print.o
	gcc -g -o run readFile.o parser.o print.o  main.o
readFile.o: readFile.c
	gcc -g -c -o readFile.o readFile.c
parser.o: parser.c
	gcc -g -c -o parser.o parser.c
print.o: print.c
	gcc -g -c -o print.o print.c
main.o: main.c
	gcc -g -c -o main.o main.c
