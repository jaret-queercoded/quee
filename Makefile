CC=clang
CCFLAGS=-Wall -Werror -pedantic -c `pkg-config --cflags sdl2 SDL2_image json-c` -std=c11
LIBS=`pkg-config --libs sdl2 SDL2_image json-c` -lm
EXEC_FILE=quee
TEST_FILE=quee_test
TEST_DIR=test
OBJDIR=objs

OBJECTS=$(addprefix $(OBJDIR)/, quee_helpers.o quee_sprite.o quee_scene.o quee_renderer.o quee_texture.o quee_managers.o)
MAIN_OBJECT=$(addprefix $(OBJDIR)/, main.o)
TEST_OBJECTS=$(addprefix $(OBJDIR)/, quee_test.o quee_scene_test.o)
TEST_OBJECTS+=$(OBJECTS)

all: $(EXEC_FILE)
test: $(TEST_FILE)
test: CCFLAGS += -DDEBUG -g

debug: CCFLAGS += -DDEBUG -g
debug: $(EXEC_FILE)

$(EXEC_FILE): CCFLAGS += -O3
$(EXEC_FILE): $(OBJECTS) $(MAIN_OBJECT) 
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $< $(CCFLAGS) -o $@

$(TEST_FILE): $(TEST_OBJECTS)
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $< $(CCFLAGS) -o $@
	

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(EXEC_FILE) $(TEST_FILE)
