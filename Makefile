CC=clang
PKGS=sdl2 SDL2_image json-c
CCFLAGS=-Wall -Werror -pedantic -DDEBUG -g -c `pkg-config --cflags $(PKGS)` -std=c11
LIBS=`pkg-config --libs $(PKGS)` -lm
EXEC_FILE=quee
TEST_FILE=quee_test
TEST_DIR=test
OBJDIR=objs

OBJECTS=$(addprefix $(OBJDIR)/, quee_helpers.o quee_entity.o quee_sprite.o quee_scene.o quee_renderer.o quee_texture.o)
MAIN_OBJECT=$(addprefix $(OBJDIR)/, main.o)
TEST_OBJECTS=$(addprefix $(OBJDIR)/$(TEST_DIR)/, main.o quee_test_helper.o quee_scene_test.o quee_texture_test.o quee_sprite_test.o)
TEST_OBJECTS+=$(OBJECTS)

all: $(EXEC_FILE)
test: $(TEST_FILE)
runtest: test
	@./$(TEST_FILE)

$(EXEC_FILE): $(OBJECTS) $(MAIN_OBJECT) 
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $< $(CCFLAGS) -o $@

$(TEST_FILE): $(TEST_OBJECTS)
	$(CC) $^ $(LIBS) -o $@

$(OBJDIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $< $(CCFLAGS) -o $@
	

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(EXEC_FILE) $(TEST_FILE)
