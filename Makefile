# Compiler and compilation flags
# -fPIC is required for shared libraries
# -g adds debug symbols for use with lldb
# -Wall turns on all major warnings, which is good practice
CC = clang
CFLAGS = -fPIC -g -Wall

# Linker flags
# -shared creates a shared library (.dylib on macOS)
LDFLAGS = -shared

# LuaJIT flags found using the pkg-config tool
LUA_CFLAGS = $(shell pkg-config --cflags luajit)
LUA_LIBS = $(shell pkg-config --libs luajit)

# Project structure
# List all your .c source files here
SRCS = src/simulation.c src/bfe.c src/basis.c
# Automatically generate a list of .o object files from the .c source files
OBJS = $(SRCS:.c=.o)
# The name of the final library we want to build
TARGET = libexpanse.dylib

# --- Targets and Rules ---

# The default target, executed when you just type "make"
all: $(TARGET)

# Rule for linking the final library from the object files
$(TARGET): $(OBJS)
	@echo "LD  $@"
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LUA_LIBS)

# A pattern rule for compiling any .c file into a .o object file
# $@ is an automatic variable meaning "the target name" (e.g., src/simulation.o)
# $< is an automatic variable meaning "the first prerequisite" (e.g., src/simulation.c)
%.o: %.c
	@echo "CC  $@"
	$(CC) $(CFLAGS) $(LUA_CFLAGS) -c $< -o $@

# A target to clean up all compiled files
clean:
	@echo "CLEAN"
	rm -f $(OBJS) $(TARGET)
