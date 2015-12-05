mdriver:	mm.o mdriver.o
	gcc -g -o mdriver mdriver.o mm.o

mm.o:	mm.c memory.h
	gcc -c -g mm.c

mdriver.o:	mdriver.c memory.h
	gcc -c -g mdriver.c

clean:	
	rm -f *.o mdriver

