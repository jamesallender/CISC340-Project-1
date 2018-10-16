CC= gcc
CFLAGS=`pkg-config --cflags gmodule-2.0`

LDFLAGS=`pkg-config --libs gmodule-2.0`

all: simulatorTest.o
	$(CC) $(CFLAGS) simulatorTest.o -o simulatorTest $(LDFLAGS)

simulatorTest.o: simulatorTest.c
	$(CC) $(CFLAGS) -c simulatorTest.c

clean:
	rm simulatorTest *.o *.*~ *~
