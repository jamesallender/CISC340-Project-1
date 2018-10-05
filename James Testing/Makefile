CC= gcc
CFLAGS=`pkg-config --cflags gmodule-2.0`

LDFLAGS=`pkg-config --libs gmodule-2.0`

all: assemblerJamesWorkingr.o
	$(CC) $(CFLAGS) assemblerJamesWorkingr.o -o assemblerJamesWorkingr $(LDFLAGS)

assemblerJamesWorkingr.o: assemblerJamesWorkingr.c
	$(CC) $(CFLAGS) -c assemblerJamesWorkingr.c -ggdb

clean:
	rm assemblerJamesWorkingr *.o *.*~ *~
