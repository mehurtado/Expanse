# Compiler and compilation flags
CC = clang
# Add -MMD and -MP to generate dependency files
CFLAGS = -fPIC -g -Wall -Isrc/vendor -MMD -MP

# Linker flags
LDFLAGS = -shared

# LuaJIT flags found using the pkg-config tool
LUA_CFLAGS = $(shell pkg-config --cflags luajit)
LUA_LIBS = $(shell pkg-config --libs luajit)

# Project structure
SRCS = src/simulation.c src/bfe.c src/basis.c
OBJS = $(SRCS:.c=.o)
# List of dependency files that will be auto-generated
DEPS = $(SRCS:.c=.d)
TARGET = libexpanse.dylib

# --- Targets and Rules ---

# The default target
all: $(TARGET)

# Rule for linking the final library
$(TARGET): $(OBJS)
	@echo "LD  $@"
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LUA_LIBS)

# A pattern rule for compiling .c to .o
# The CFLAGS now include -MMD -MP, which creates a .d file for each .c file
%.o: %.c
	@echo "CC  $@"
	$(CC) $(CFLAGS) $(LUA_CFLAGS) -c $< -o $@

# Clean up all compiled files AND the dependency files
clean:
	@echo "CLEAN"
	rm -f $(OBJS) $(DEPS) $(TARGET)

# Tell make to include all the auto-generated dependency files.
# This makes it aware of all the .h file dependencies.
-include $(DEPS)