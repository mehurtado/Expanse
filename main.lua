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

    void simulation_step(SimulationState* state, double dt);
    void load_simulation_state(const char* filename, SimulationState* state);
    void apply_forces(SimulationState* state);
]]

-- 3. Load our compiled C library
local sim_lib = ffi.load("./libsimulation.dylib")

-- 4. Now, write the main application logic entirely in Lua!

print("Lua Engine: Initializing simulation...")

-- Create an instance of our C struct directly from Lua
local state = ffi.new("SimulationState")

-- Call our C function to load the initial conditions
sim_lib.load_simulation_state("init.txt", state)

if state.particle_count == 0 then
    print("Failed to load particles. Exiting.")
    return
end

print("Loaded " .. state.particle_count .. " particle(s). Starting simulation...")

local dt = 3600 * 24 -- Timestep of one day
local num_steps = 365

-- Initial force calculation
sim_lib.apply_forces(state)

for i = 0, num_steps do
    if i % 10 == 0 then
        -- Access C struct members directly from Lua
        local p = state.particles[0]
        print(string.format("Day %3d: Pos=(%.2e, %.2e, %.2e)", i, p.position[0], p.position[1], p.position[2]))
    end

    -- Call the C function to advance the simulation
    sim_lib.simulation_step(state, dt)
end

