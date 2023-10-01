CC=gcc
CFLAGS=-Wall
CLEAN=rm -f

all: compile-client link-client \
     compile-server link-server

compile-client:
	make -C client

link-client:
	$(CC) $(CFLAGS) -o myclient client/*.o -lpthread

compile-server:
	make -C server

link-server:
	$(CC) $(CFLAGS) -o myserver server/*.o

clean:
	make -C client clean
	make -C server clean
	$(CLEAN) myclient myserver mysocket
