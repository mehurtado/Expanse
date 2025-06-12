-- main.lua
print("Lua: Script started.")

print("Lua: About to call the C function 'c_hello'.")

-- This looks like a normal Lua function call, but it will execute our C code.
c_hello("Matthew from Lua")

print("Lua: C function returned.")-- main.lua
print("Hello from Lua! The simulation engine is now scriptable.")
