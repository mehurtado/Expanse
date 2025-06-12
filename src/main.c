// src/main.c
#include <stdio.h>

// Include the necessary Lua headers
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main() {
    // 1. Create a new Lua state (interpreter instance)
    lua_State *L = luaL_newstate();
    if (L == NULL) {
        fprintf(stderr, "Error creating Lua state.\n");
        return 1;
    }

    // 2. Load the standard Lua libraries (print, math, etc.)
    luaL_openlibs(L);

    printf("C engine: Loading and running main.lua...\n");

    // 3. Load and run the Lua script
    int result = luaL_dofile(L, "main.lua");
    if (result != LUA_OK) {
        // If there's an error, it will be on top of the stack.
        // Print it to the console.
        const char* error_msg = lua_tostring(L, -1);
        fprintf(stderr, "Lua error: %s\n", error_msg);
        lua_pop(L, 1); // Remove error message from stack
    }

    printf("C engine: Script finished.\n");

    // 4. Clean up and close the Lua state
    lua_close(L);

    return 0;
}