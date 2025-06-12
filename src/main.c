// src/main.c
#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// --- NEW C FUNCTION TO EXPOSE TO LUA ---
// All functions callable from Lua must have this signature:
// It takes the lua_State and returns the number of results pushed to the stack.
static int l_c_hello(lua_State *L) {
    // 1. Get the first argument passed from the Lua script.
    // luaL_checkstring confirms it's a string and gets its value.
    const char* name = luaL_checkstring(L, 1);

    // 2. Do something with it in C.
    printf("Hello from C, %s!\n", name);

    // 3. Return the number of values we are giving back to Lua (in this case, none).
    return 0;
}

int main() {
    // 1. Create a new Lua state
    lua_State *L = luaL_newstate();
    if (L == NULL) { /* ... error handling ... */ return 1; }
    luaL_openlibs(L);

    // --- NEW REGISTRATION STEP ---
    // Register our C function `l_c_hello` with Lua under the global name "c_hello".
    lua_register(L, "c_hello", l_c_hello);

    printf("C engine: Loading and running main.lua...\n");

    // 3. Load and run the Lua script
    int result = luaL_dofile(L, "main.lua");
    if (result != LUA_OK) { /* ... error handling ... */ }

    printf("C engine: Script finished.\n");

    // 4. Clean up and close the Lua state
    lua_close(L);

    return 0;
}