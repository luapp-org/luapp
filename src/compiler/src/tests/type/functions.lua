-- The function definition is legal 
local function func(a: number, b: string): boolean 
    -- Error --> type mismatch
    local c: boolean = a
end