--[[ First type of numeric forloop test ]]--

-- ERROR (no type annotation)
for i = 0, 10, -1 do
    -- stuff
end

-- This should work fine
for i: number = 0, 10 do
    -- do stuff
end

local array: Array<string> = { "" }

for array[0] = 1, 10, 2 do
    -- do stuff
end