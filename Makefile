CC=gcc
CFLAGS=-Wall -Werror -pedantic -c `pkg-config --cflags sdl2` -std=c11
LIBS=`pkg-config --libs sdl2`
EXEC_FILE=quee
OBJDIR=objs

OBJECTS= $(addprefix $(OBJDIR)/, main.o)

all: make_obj_dir $(EXEC_FILE)

make_obj_dir:
	mkdir -p $(OBJDIR)

$(EXEC_FILE): $(OBJECTS) 
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR) objs/%.o: %.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXEC_FILE)
