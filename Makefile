CC=gcc
CFLAGS=-Wall -Werror -pedantic -c `pkg-config --cflags sdl2` -std=c11
LFLAGS=`pkg-config --libs sdl2`
EXEC_FILE=quee

OBJECTS=main.o

all: $(EXEC_FILE)

$(EXEC_FILE): main.o 
	$(CC) $^ $(LFLAGS) -o $@

$(OBJECTS): %.o: %.c
	$(CC) $< $(CFLAGS) -o $@

clean:
	rm -f *.o $(EXEC_FILE)
