all: dron.exe
dron.exe: dron.o funcdron.o
	gcc -o dron dron.o funcdron.o
dron.o: dron.c libdron.h
	gcc -c --std=c99 -o dron.o dron.c
funcdron.o: funcdron.c
	gcc -c --std=c99 -o funcdron.o funcdron.c
clean:
	del *.o
	del dron.exe

