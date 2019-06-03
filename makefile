run: readFile.o parser2.o main.o print.o
	gcc -g -o run readFile.o parser2.o print.o  main.o
readFile.o: readFile.c
	gcc -g -c -o readFile.o readFile.c
parser2.o: parser2.c
	gcc -g -c -o parser2.o parser2.c
print.o: print.c
	gcc -g -c -o print.o print.c
main.o: main.c
	gcc -g -c -o main.o main.c
