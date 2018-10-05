CC= gcc
CFLAGS=`pkg-config --cflags gmodule-2.0`

LDFLAGS=`pkg-config --libs gmodule-2.0`

all: assemblerJamesWorking.o
	$(CC) $(CFLAGS) assemblerJamesWorking.o -o assemblerJamesWorking $(LDFLAGS)

assemblerJamesWorking.o: assemblerJamesWorking.c
	$(CC) $(CFLAGS) -c assemblerJamesWorking.c -ggdb

clean:
	rm assemblerJamesWorking *.o *.*~ *~
