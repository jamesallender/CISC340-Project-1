CC= gcc
CFLAGS=`pkg-config --cflags gmodule-2.0`

LDFLAGS=`pkg-config --libs gmodule-2.0`

all: assembler.o
	$(CC) $(CFLAGS) assembler.o -o assembler $(LDFLAGS)

assembler.o: assembler.c
	$(CC) $(CFLAGS) -c assembler.c

clean:
	rm assembler *.o *.*~ *~
