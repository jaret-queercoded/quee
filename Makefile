CC=gcc
CFLAGS=-g -Wall -Werror -pedantic -c `pkg-config --cflags sdl2 SDL2_image` -std=c11
LIBS=`pkg-config --libs sdl2 SDL2_image` -lm
EXEC_FILE=quee
OBJDIR=objs

OBJECTS= $(addprefix $(OBJDIR)/, main.o quee_helpers.o quee_sprite.o)

all: make_obj_dir $(EXEC_FILE)

make_obj_dir:
	mkdir -p $(OBJDIR)

$(EXEC_FILE): $(OBJECTS) 
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR) : %.c
	$(CC) $< $(CFLAGS) -o $@
objs/%.o: %.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXEC_FILE)
