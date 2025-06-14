--[[
    Expanse Simulation Engine: Main Script
    - Initializes the C library via LuaJIT's FFI.
    - Contains unit tests for core mathematical basis functions.
    - Contains the main logic for running a full simulation.
--]]

-- --- 1. Initialization and FFI Definitions ---
print("--- Initializing Expanse ---")
local ffi = require("ffi")

-- Define all C structs and function prototypes for the FFI.
-- This is a complete reflection of all your project's .h files.
ffi.cdef[[
    // From particle.h
    typedef struct {
        double mass;
        double position[3];
        double velocity[3];
        double acceleration[3];
        int id;
    } Particle;

    // From bfe.h
    typedef struct {
        int nmax;
        int lmax;
        double scale_radius;
        double* S_coeffs;
        double* T_coeffs;
    } BFEModel;

    // From simulation.h 
    typedef struct {
        Particle* particles;
        int particle_count;
        int particle_capacity;
        BFEModel* model;
        double current_time;
    } SimulationState;

    // From basis.h
    void basis_sincos(int mmax, double phi, double* c, double* s);
    void basis_legendre_deriv(int lmax, double x, double* p, double* dp);

    // From simulation.h
    SimulationState* simulation_create();
    void simulation_destroy(SimulationState* state);
    int simulation_load_particles(SimulationState* state, const char* filename);
    void simulation_step(SimulationState* state, double dt);
]]

-- Load the compiled C shared library
local ExpanseLib = ffi.load("./libexpanse.dylib")
print("... C library loaded successfully.\n")


-- --- 2. Unit Test Functions ---

function test_basis_functions()
    print("--- Running Unit Test: basis_sincos ---")
    local mmax = 5
    local phi = math.pi / 6.0 -- pi/6 radians
    local c = ffi.new("double[?]", mmax + 1)
    local s = ffi.new("double[?]", mmax + 1)
    ExpanseLib.basis_sincos(mmax, phi, c, s)
    for m = 0, mmax do
        print(string.format("m=%d, cos(m*phi)=%.4f, sin(m*phi)=%.4f", m, c[m], s[m]))
    end
    print("... basis_sincos test complete.\n")

    print("--- Running Unit Test: basis_legendre_deriv ---")
    local lmax = 4
    local x = 0.5
    local size = (lmax + 1) * (lmax + 1)
    local stride = lmax + 1
    local p = ffi.new("double[?]", size)
    local dp = ffi.new("double[?]", size)
    ExpanseLib.basis_legendre_deriv(lmax, x, p, dp)
    print("... P_l^m(x) values:")
    for l = 0, lmax do
        local row_str = string.format("l=%d:", l)
        for m = 0, l do
            row_str = row_str .. string.format(" %.4f", p[l * stride + m])
        end
        print(row_str)
    end
    print("... basis_legendre_deriv test complete.\n")
end


-- --- 3. Main Simulation Logic ---

function run_simulation()
    print("--- Running Main Simulation ---")
    local state_ptr = ExpanseLib.simulation_create()
    if state_ptr == nil then
        print("Error: C failed to create simulation state.")
        return
    end
    print("... C simulation state created.")

    local count = ExpanseLib.simulation_load_particles(state_ptr, "init.txt")
    state_ptr.particle_count = count
    print("... Loaded " .. state_ptr.particle_count .. " particle(s).")
    if state_ptr.particle_count == 0 then
        ExpanseLib.simulation_destroy(state_ptr)
        return
    end

    print("... Starting simulation loop.")
    local dt = 3600 * 24 -- Timestep of one day
    local num_steps = 365
    for i = 1, num_steps do
        ExpanseLib.simulation_step(state_ptr, dt)
        if i % 30 == 0 then -- Print status every 30 days
            local p = state_ptr.particles[0]
            print(string.format("Day %d: Pos=(%.2e, %.2e, %.2e)", i, p.position[0], p.position[1], p.position[2]))
        end
    end
    print("... Simulation finished.")

    print("... Cleaning up C memory.")
    ExpanseLib.simulation_destroy(state_ptr)
    print("--- Main Simulation Complete ---\n")
end


-- --- 4. Execution ---

-- Run the tests first to verify math functions
test_basis_functions()

-- Then run the main simulation
run_simulation()

print("All tasks finished.")