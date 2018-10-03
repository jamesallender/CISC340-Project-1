CC= gcc
CFLAGS=-pipe

all: assembler.o
	$(CC) $(CFLAGS) assembler.o -o assembler

hello.o: assembler.c
	$(CC) $(CFLAGS) -c assembler.c

clean: 
	rm hello *.o *.*~ *~
