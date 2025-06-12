// src/astraeus.c
#include "simulation.h" // Your existing simulation logic
#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define SIMULATION_META "Astraeus.Simulation"

// --- API Functions ---

// Creates a new SimulationState object and pushes it onto the Lua stack
static int l_new_simulation(lua_State *L) {
    // 1. Allocate memory for our struct within Lua's garbage collector
    SimulationState *sim = (SimulationState*)lua_newuserdatauv(L, sizeof(SimulationState), 0);

    // 2. Initialize its values
    sim->particle_count = 0;
    sim->current_time = 0.0;

    // 3. Attach the metatable (our "class" definition) to the userdata
    luaL_setmetatable(L, SIMULATION_META);

    // 4. Return the new object (which is already on the stack)
    return 1;
}

// A "getter" method to retrieve the simulation's current time
static int l_get_time(lua_State *L) {
    // 1. Get the simulation object from argument 1 (the 'self' or 'sim' object)
    SimulationState *sim = (SimulationState*)luaL_checkudata(L, 1, SIMULATION_META);

    // 2. Push the value we want to return onto the stack
    lua_pushnumber(L, sim->current_time);

    // 3. Return the number of results (we are returning 1 value)
    return 1;
}

// --- Library Registration ---

// Define the methods for our "Simulation" class
static const struct luaL_Reg simulation_methods[] = {
    { "get_time", l_get_time },
    // We will add "step", "load", etc. here later
    { NULL, NULL } // Sentinel
};

// Define the global functions for our library
static const struct luaL_Reg astraeus_lib[] = {
    { "new", l_new_simulation },
    { NULL, NULL } // Sentinel
};

// This function is called by Lua when we `require('astraeus')`
int luaopen_astraeus(lua_State *L) {
    // Create the metatable for our Simulation object
    luaL_newmetatable(L, SIMULATION_META);
    // Make the metatable its own index (for object:method() calls)
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    // Register the methods
    luaL_setfuncs(L, simulation_methods, 0);

    // Register the main library of global functions
    luaL_newlib(L, astraeus_lib);
    return 1;
}