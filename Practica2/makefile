all:	init getty shell

init:	init.c
	gcc -c init.c -o init.o
	gcc -o init.exe init.o

getty:	getty.c
	gcc -c getty.c -o getty.o
	gcc -o getty.exe getty.o

shell:	shell.c
	gcc -c shell.c -o shell.o
	gcc -o shell.exe shell.o

clean:	
	rm init.o getty.o shell.o
