CC= gcc
CFLAGS=`pkg-config --cflags gmodule-2.0`

LDFLAGS=`pkg-config --libs gmodule-2.0`

all: simulator.o
	$(CC) $(CFLAGS) simulator.o -o simulator $(LDFLAGS)

simulator.o: simulator.c
	$(CC) $(CFLAGS) -c simulator.c

clean:
	rm simulator *.o *.*~ *~
