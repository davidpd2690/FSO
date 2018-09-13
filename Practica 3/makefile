all:	serialpi threadpi clonepi forkpi

serialpi:	serialpi.c
	gcc -c serialpi.c -o serialpi.o -lm
	gcc -o serialpi.exe serialpi.o -lm

threadpi:	threadpi.c
	gcc -c threadpi.c -o threadpi.o -lm -lpthread
	gcc -o threadpi.exe threadpi.o -lm -lpthread

clonepi:	clonepi.c
	gcc -c clonepi.c -o clonepi.o -lm
	gcc -o clonepi.exe clonepi.o -lm

forkpi:		forkpi.c
	gcc -c forkpi.c -o forkpi.o -lm
	gcc -o forkpi.exe forkpi.o -lm

clean:	
	rm serialpi.o threadpi.o clonepi.o forkpi.o
