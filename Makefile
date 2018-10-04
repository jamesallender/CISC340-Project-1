CC= gcc
CFLAGS=`pkg-config --cflags gmodule-2.0`

LDFLAGS=`pkg-config --libs gmodule-2.0`

all: assemblerCopy.o
	$(CC) $(CFLAGS) assemblerCopy.o -o assemblerCopy $(LDFLAGS)

assemblerCopy.o: assemblerCopy.c
	$(CC) $(CFLAGS) -c assemblerCopy.c -ggdb

clean:
	rm assemblerCopy *.o *.*~ *~
