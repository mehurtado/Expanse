-- main.lua

-- 1. Load the FFI library
local ffi = require("ffi")

-- 2. Define the C data structures and function prototypes for the FFI.
--    This tells LuaJIT what the C code looks like.
--    You can literally copy-paste your .h file contents here.
ffi.cdef[[
    // From particle.h
    typedef struct {
        double mass;
        double position[3];
        double velocity[3];
        double acceleration[3];
        int id;
    } Particle;

    // From simulation.h
    // #define MAX_PARTICLES 128
    typedef struct {
        Particle particles[128];
        int particle_count;
        double current_time;
    } SimulationState;

    SimulationState* simulation_create();
    void simulation_destroy(SimulationState* state);
    void simulation_step(SimulationState* state, double dt);
    void simulation_load_particles(SimulationState* state, const char* filename);
    void apply_forces(SimulationState* state);
]]

-- 3. Load our compiled C library
local sim_lib = ffi.load("./libsimulation.dylib")

-- 1. Ask C to create the simulation state
print("Lua: Creating simulation object...")
local state_ptr = sim_lib.simulation_create()

-- Error check
if state_ptr == nil then
    print("Error: C failed to create simulation state.")
    return
end

-- 2. Ask C to load data into the state
print("Lua: Loading particles...")
sim_lib.simulation_load_particles(state_ptr, "init.txt")

-- 3. Run the simulation loop
print("Lua: Starting simulation loop...")
local dt = 3600 * 24
for i = 0, 365 do
    sim_lib.simulation_step(state_ptr, dt)
end
print("Lua: Simulation finished.")

-- 4. Ask C to clean up the memory
print("Lua: Destroying simulation object...")
sim_lib.simulation_destroy(state_ptr)
print("Lua: Done.")
