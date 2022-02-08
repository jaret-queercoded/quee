CC=clang
PKGS=sdl2 SDL2_image json-c
CCFLAGS=-Wall -Werror -pedantic -DDEBUG -g -c `pkg-config --cflags $(PKGS)` -Ilua/ -std=c11
LIBS=`pkg-config --libs $(PKGS)` -lm -Llua/ -llua -ldl 
EXEC_FILE=quee
TEST_FILE=quee_test
TEST_DIR=test
OBJDIR=objs

OBJECTS=$(addprefix $(OBJDIR)/, quee_helpers.o quee_entity.o quee_sprite.o quee_scene.o quee_renderer.o quee_texture.o quee_script.o quee_script_functions.o)
MAIN_OBJECT=$(addprefix $(OBJDIR)/, main.o)
TEST_OBJECTS=$(addprefix $(OBJDIR)/$(TEST_DIR)/, main.o quee_test_helper.o quee_scene_test.o quee_texture_test.o quee_sprite_test.o quee_script_test.o)
TEST_OBJECTS+=$(OBJECTS)

LUA=lua/liblua.a

all: lua $(EXEC_FILE) 
test: lua $(TEST_FILE) 
	@./$(TEST_FILE)

lua: 
	curl -R -O http://www.lua.org/ftp/lua-5.4.4.tar.gz
	@tar zxf lua-5.4.4.tar.gz
	cd lua-5.4.4 && make all test
	@mkdir lua
	@cp lua-*/src/{lua,luaconf,lauxlib,lualib}.h lua
	@cp lua-*/src/liblua.a lua
	@rm lua*.tar.gz

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

.PHONY: lua_clean
lua_clean:
	rm -rf lua/
