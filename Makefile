all:
	gcc -o main src/main.c src/lectura.c src/analisis.c

run: all
	./main.exe