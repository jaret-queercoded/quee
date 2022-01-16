CC=gcc
CCFLAGS=-Wall -Werror -pedantic -c `pkg-config --cflags sdl2 SDL2_image json-c` -std=c11
LIBS=`pkg-config --libs sdl2 SDL2_image json-c` -lm
EXEC_FILE=quee
OBJDIR=objs

OBJECTS= $(addprefix $(OBJDIR)/, main.o quee_helpers.o quee_sprite.o quee_scene.o)

all: $(EXEC_FILE)

debug: CCFLAGS += -DDEBUG -g
debug: $(EXEC_FILE)

$(EXEC_FILE): $(OBJECTS) 
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $< $(CCFLAGS) -o $@
$(OBJDIR):
	mkdir $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXEC_FILE)
